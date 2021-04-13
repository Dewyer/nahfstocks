#include "Exchange.h"

#include <utility>
#include "../../lib/types.h"
#include "exchange_api/MarketContext.h"
#include "exchange_api/ExchangeApi.h"

using nhflib::Rc;
using nhflib::Vector;

exchange::Exchange::Exchange(const Rc<nhflib::RandomProvider> &rng,
							 const Rc<config::Config> &config,
							 const Rc<Vector<Company>> &companies,
							 const Rc<Vector<TraderAgent>> &trader_agents) {
	this->rng = rng;
	this->config = config;
	this->companies = companies;

	usize median_cash = this->config->get_median_starting_cash();

	std::cout << "Generating Trader Records:" << std::endl;
	usize trader_id = 0;
	this->mean_traders_per_cycle = trader_agents->size()/5;
	this->traders = nhflib::make_rc_ctr<Vector<TraderRecordInExchange>>();

	for (usize ii = 0; ii < trader_agents->size(); ii++) {
		auto trader = trader_agents->at(ii);
		usize cash = this->rng->next_usize_normal(0, median_cash * 2, median_cash, median_cash * 0.5);
		usize income = this->rng->next_usize_normal(cash * 0.10, cash * 1.5, cash * 0.3, cash * 0.20);

		TraderRecordInExchange rec(trader_id++, trader, cash, income);
		rec.next_random_activation(this->rng, 0, this->mean_traders_per_cycle);
		rec.print_debug(std::cout);
		this->traders->push_back(rec);
	}
}

void exchange::Exchange::cycle() {
	this->cycle_count++;

	std::cout << "cycle" << std::endl;
	this->handle_fixed_income_on_cycle();
	this->handle_trader_agent_activation();
}

void exchange::Exchange::handle_fixed_income_on_cycle() {
	if (this->cycle_count % this->config->get_fixed_income_interval() != 0) {
		return;
	}

	this->traders->for_each([](Rc<TraderRecordInExchange> trader_rec) {
		trader_rec->cash_balance += trader_rec->fixed_income;
	});
}

void exchange::Exchange::handle_trader_agent_activation() {
	MarketContext market(this->companies);
	auto m_rc = nhflib::make_rc(market);

	this->traders->for_each([this, &m_rc](Rc<TraderRecordInExchange> trader_rec){
		if (this->cycle_count < trader_rec->next_activation)
			return ;

		ExchangeApi api(this, m_rc ,trader_rec, &std::cout);

		trader_rec->trader->on_cycle(api);
		trader_rec->next_random_activation(this->rng, this->cycle_count, this->mean_traders_per_cycle);

	});
}

bool sort_orders(Rc<exchange::Order> then, Rc<exchange::Order> that) {
	if (then->target_price == that->target_price) {
		return then->amount > that->amount;
	}

	return then->target_price > that->target_price;
}

exchange::Order exchange::Exchange::open_order(Rc<TraderRecordInExchange> trader, exchange::OrderCreationPayload order) {
	auto comp_target = this->companies->find([&order](Rc<Company> cmp){
		return cmp->get_id() == order.company_id;
	});

	if (!comp_target) {
		throw std::runtime_error("No such company");
	}

	usize total_balance_required = order.get_total_price();

	if (trader->available_balance < total_balance_required) {
		throw std::runtime_error("Not enough balance!");
	}

	trader->available_balance -= total_balance_required;

	auto ord = exchange::Order {
		++this->last_order_id,
		trader->trader_id,
		trader,
		order
	};

	auto ord_rc = nhflib::make_rc(ord);
	comp_target->orders.sorted_push_back(ord_rc, sort_orders);
	trader->open_orders.push_back(ord_rc);

	return ord;
}

void exchange::Exchange::cancel_order(Rc<TraderRecordInExchange> trader, usize order_id) {
	auto comp_target = this->companies->find([order_id](Rc<Company> cmp){
		return cmp->get_id() == order_id;
	});

	auto order_target = trader->open_orders.find([order_id](Rc<exchange::Order> ord){
		return ord->id == order_id;
	});

	comp_target->orders.remove([order_id](Rc<exchange::Order> ord){
		return ord->id == order_id;
	});

	trader->open_orders.remove([order_id](Rc<exchange::Order> ord){
		return ord->id == order_id;
	});

	trader->available_balance += order_target->get_total_price();
}

void exchange::Exchange::execute_open_auction() {
	this->companies->for_each([this](Rc<Company> cmp){
		for (usize ii = 0; ii < cmp->orders.size(); ii++) {
			auto at_order = cmp->orders[ii];

			if (at_order->type != exchange::OrderType::Buy) {
				continue;
			}

			for (usize kk = ii-1; ; kk--) {
				auto sell_order = cmp->orders[kk];
				if (sell_order->type == exchange::OrderType::Buy || sell_order->amount == 0 || at_order->trader->trader_id == sell_order->trader->trader_id) {
					continue;
				}

				this->execute_orders(at_order, sell_order);
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

	usize buy_target = buy_order->get_total_price();

	buy_order->amount -= exchanged_am;
	buy_order->trader->available_balance += buy_target - total_sale_price;
	buy_order->trader->cash_balance -= total_sale_price;
	sell_order->amount -= exchanged_am;
	sell_order->trader->cash_balance += total_sale_price;
	sell_order->trader->available_balance += total_sale_price;
}

void exchange::Exchange::clear_executed_orders() {
	this->companies->for_each([this](Rc<Company> cmp) {
		cmp->orders.filter_in_place([](Rc<Order> ord){
			return ord->amount <= 0;
		});
	});

	this->traders->for_each([this](Rc<TraderRecordInExchange> trader) {
		trader->open_orders.filter_in_place([](Rc<Order> ord){
			return ord->amount <= 0;
		});
	});
}
