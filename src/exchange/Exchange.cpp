#include "Exchange.h"

#include <utility>
#include "../../lib/types.h"
#include "exchange_api/MarketContext.h"
#include "exchange_api/ExchangeApi.h"
#include "exchange_api/TraderRecordInExchange.h"
#include "../company/CompanyAgent.h"

using nhflib::Rc;
using nhflib::Vector;
using exchange::TraderRecordInExchange;
using trader::TraderAgentInitPayload;

exchange::Exchange::Exchange(const Rc<nhflib::RandomProvider> &rng,
							 const Rc<config::Config> &config,
							 const Rc<Vector<Company>> &companies,
							 const Rc<Vector<TraderAgent>> &trader_agents,
							 const Rc<Vector<company::CompanyAgent>> &company_agents,
							 const Rc<CliHelper> &_cli) {
	this->rng = rng;
	this->config = config;
	this->cli = _cli;
	this->companies = companies;
	this->mean_traders_per_cycle = trader_agents->size() / 5;
	this->setup_traders(trader_agents, company_agents);
	this->last_order_id = 0;
	this->runtime_exception_occured = false;
	this->cycle_count = 0;
}

void exchange::Exchange::setup_traders(
		const Rc<Vector<TraderAgent>> &trader_agents,
		const Rc<Vector<company::CompanyAgent>> &company_agents) {

	usize trader_id = 0;
	this->traders = nhflib::make_rc_ctr<Vector<TraderRecordInExchange>>();

	for (usize ii = 0; ii < trader_agents->size(); ii++) {
		auto rec = this->create_trader_record(trader_agents->at(ii), trader_id);
		this->traders->push_back(rec);
	}

	for (usize ii = 0; ii < company_agents->size(); ii++) {
		auto company_trader = company_agents->at(ii);
		auto company_target = this->companies->find([&company_trader](Rc<Company> cmp) {
			return cmp->get_id() == company_trader->get_company();
		});

		TraderRecordInExchange rec(trader_id++, company_trader.base_rc<TraderAgent>(), 0, 0);
		auto shares_to_add = static_cast<i32>(company_target->get_outstanding_shares());
		rec.add_or_sub_stocks_and_free_stocks(company_trader->get_company(), shares_to_add, shares_to_add);

		this->traders->push_back(rec);
	}

	this->init_traders();
}


Rc<TraderRecordInExchange> exchange::Exchange::create_trader_record(const Rc<TraderAgent> &trader, usize &trader_id) {
	usize median_cash = this->config->get_median_starting_cash();

	usize cash = this->rng->next_usize_normal(0, median_cash * 2, median_cash, median_cash * 0.5);
	usize income = this->rng->next_usize_normal(cash * 0.10, cash * 1.5, cash * 0.3, cash * 0.20);

	TraderRecordInExchange rec(trader_id++, trader, cash, income);
	rec.next_random_activation(this->rng, 0, this->mean_traders_per_cycle);

	return nhflib::make_rc(rec);
}


void exchange::Exchange::cycle() {
	this->cycle_count++;

	this->handle_fixed_income_on_cycle();
	this->recalculate_prices_on_cycle();
	this->handle_company_price_sampling();
	this->handle_trader_agent_activation();

	this->execute_open_auction();
}

void exchange::Exchange::handle_fixed_income_on_cycle() {
	if (this->cycle_count % this->config->get_fixed_income_interval() != 0) {
		return;
	}

	this->traders->for_each([](Rc<TraderRecordInExchange> trader_rec) {
		trader_rec->total_balance += trader_rec->fixed_income;
	});
}

void exchange::Exchange::handle_trader_agent_activation() {
	MarketContext market(this->companies);
	auto m_rc = nhflib::make_rc(market);

	this->traders->for_each([this, &m_rc](Rc<TraderRecordInExchange> trader_rec) {
		if (this->cycle_count < trader_rec->next_activation)
			return;

		ExchangeApi api(this, m_rc, trader_rec, this->cli);

		try {
			trader_rec->trader->on_cycle(api);
		} catch (std::runtime_error &err) {
			this->runtime_exception_occured = true;
			this->cli->os() << "Uncaught exception thrown to trader: " << err.what();
			this->cli->print_ln();
		}

		trader_rec->next_random_activation(this->rng, this->cycle_count, this->mean_traders_per_cycle);

	});
}


Option<String> exchange::Exchange::get_order_validation_error(Rc<TraderRecordInExchange> trader,
															  const exchange::OrderCreationPayload &order) {
	if (order.type == OrderType::Buy) {
		usize total_balance_required = order.get_total_price();

		if (trader->available_balance < total_balance_required) {
			return Option<String>("Not enough balance to open buy order!");
		}
	} else {
		auto comp_owned = trader->stocks.find([&order](Rc<TraderStock> stock) {
			return stock->company_id == order.company_id;
		});

		if (!comp_owned) {
			return Option<String>("Trader doesn't own any shares of this company!");
		}

		if (comp_owned->free_amount < order.amount) {
			return Option<String>("Trader doesn't own enough free shares to open this order!");
		}
	}

	return Option<String>();
}


exchange::Order
exchange::Exchange::open_order(Rc<TraderRecordInExchange> trader, exchange::OrderCreationPayload order) {
	auto comp_target = this->companies->find([&order](Rc<Company> cmp) {
		return cmp->get_id() == order.company_id;
	});

	if (!comp_target) {
		throw std::runtime_error("No such company");
	}

	auto validation_err = Exchange::get_order_validation_error(trader, order);
	if (validation_err)
		throw std::runtime_error(validation_err.unwrap().c_str());

	if (order.type == OrderType::Buy) {
		trader->available_balance -= order.get_total_price();
	} else {
		trader->add_or_sub_stocks_and_free_stocks(order.company_id, 0, -static_cast<i32>(order.amount));
	}

	auto ord = exchange::Order{
			++this->last_order_id,
			trader->trader_id,
			trader,
			order
	};

	auto ord_rc = nhflib::make_rc(ord);
	comp_target->add_order(ord_rc);
	trader->open_orders.push_back(ord_rc);

	return ord;
}

void exchange::Exchange::cancel_order(Rc<TraderRecordInExchange> trader, usize order_id) {
	auto comp_target = this->companies->find([order_id](Rc<Company> cmp) {
		return cmp->orders.some([order_id](Rc<Order> cmp_ord) {
			return cmp_ord->id == order_id;
		});
	});

	auto order_target = trader->open_orders.find([order_id](Rc<exchange::Order> ord) {
		return ord->id == order_id;
	});

	if (!comp_target || !order_target) {
		throw std::runtime_error("Order with id doesn't exists");
	}


	comp_target->orders.remove([order_id](Rc<exchange::Order> ord) {
		return ord->id == order_id;
	});

	trader->open_orders.remove([order_id](Rc<exchange::Order> ord) {
		return ord->id == order_id;
	});

	if (order_target->type == OrderType::Buy)
		trader->available_balance += order_target->get_total_price();
	else
		trader->add_or_sub_stocks_and_free_stocks(order_target->company_id, 0, order_target->amount);
}

void exchange::Exchange::execute_open_auction() {
	this->companies->for_each([](Rc<Company> cmp) {
		for (usize ii = 1; ii < cmp->orders.size(); ii++) {
			auto at_order = cmp->orders[ii];

			if (at_order->type != exchange::OrderType::Buy) {
				continue;
			}

			for (usize kk = ii - 1;; kk--) {
				auto sell_order = cmp->orders[kk];
				if (sell_order->type == exchange::OrderType::Buy || sell_order->amount == 0 ||
					at_order->trader->trader_id == sell_order->trader->trader_id) {
					continue;
				}

				Exchange::execute_orders(at_order, sell_order);
				if (at_order->amount == 0) {
					break;
				}

				if (kk == 0) {
					break;
				}
			}
		}
	});

	this->clear_executed_orders();
}

void exchange::Exchange::execute_orders(Rc<Order> buy_order, Rc<Order> sell_order) {
	usize exchanged_am = std::min(sell_order->amount, buy_order->amount);
	usize exchange_price = (sell_order->target_price + buy_order->target_price) / 2;
	usize total_sale_price = exchange_price * exchanged_am;
	auto exchanged_company = buy_order->company_id;

	usize buy_target = buy_order->get_total_price();

	buy_order->amount -= exchanged_am;
	buy_order->trader->available_balance += buy_target - total_sale_price;
	buy_order->trader->total_balance -= total_sale_price;
	sell_order->amount -= exchanged_am;
	sell_order->trader->total_balance += total_sale_price;
	sell_order->trader->available_balance += total_sale_price;

	buy_order->trader->add_or_sub_stocks_and_free_stocks(exchanged_company, exchanged_am, exchanged_am);
	sell_order->trader->add_or_sub_stocks_and_free_stocks(exchanged_company, -exchanged_am, -exchanged_am);
}

void exchange::Exchange::clear_executed_orders() {
	this->companies->for_each([](Rc<Company> cmp) {
		cmp->orders.filter_in_place([](Rc<Order> ord) {
			return ord->amount > 0;
		});
	});

	this->traders->for_each([](Rc<TraderRecordInExchange> trader) {
		trader->open_orders.filter_in_place([](Rc<Order> ord) {
			return ord->amount > 0;
		});
	});
}

void exchange::Exchange::recalculate_prices_on_cycle() {
	this->companies->for_each([](Rc<Company> cmp) {
		cmp->recalculate_bid_ask();
	});
}

ExchangeStats exchange::Exchange::get_stats() {
	auto total_money = (usize) 0;
	auto at_cycles = this->get_cycle_count();
	auto biggest_cmp = this->get_biggest_company();
	auto richest_trader = this->get_richest_trader();

	for (usize ii = 0; ii < this->traders->size(); ii++) {
		auto trader = this->traders->at(ii);
		total_money += trader->total_balance;
	}

	return ExchangeStats{
			total_money,
			biggest_cmp,
			richest_trader,
			at_cycles
	};
}

Rc<Company> exchange::Exchange::get_biggest_company() {
	return this->companies->max([](Rc<Company> cmp) {
		return cmp->get_market_cap();
	});
}

Rc<TraderRecordInExchange> exchange::Exchange::get_richest_trader() {
	return this->traders->max([](Rc<TraderRecordInExchange> trader) {
		return trader->total_balance;
	});
}

void exchange::Exchange::handle_company_price_sampling() {
	if (this->cycle_count % this->config->get_price_sampling_rate() != 0) {
		return;
	}

	for (auto cmp : *this->companies) {
		cmp->take_price_sample(this->cycle_count);
	}
}

void exchange::Exchange::init_traders() {
	for (auto trader: *this->traders) {
		trader->trader->init(TraderAgentInitPayload {
			trader->trader_id,
		});
	}
}
