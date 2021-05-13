#include "NormalTraderAgent.h"
#include "../exchange/exchange_api/ExchangeApi.h"
#include "../exchange/exchange_api/TraderRecordInExchange.h"

using exchange::TraderStock;

void trader::NormalTraderAgent::choose_random_settings() {
	auto get_norm_normal = [this]() {
		return this->rng->next_f64_normal(0, 1, 0.5, 0.2);
	};

	this->position_count = this->rng->next_usize(1, this->config->get_max_trader_positions());
	this->finance_bias = get_norm_normal();
	this->leadership_bias = get_norm_normal();
	this->sector_focus = this->rng->next_normal();
	this->focus_sector_threshold = get_norm_normal();
	this->volume_sensitivity = get_norm_normal();
	this->price_sensitivity = get_norm_normal();
	this->nonce_focus = this->rng->next_f64(0, 1);
	this->stop_loss = get_norm_normal() + 0.2;
	this->bought_bias = get_norm_normal() / 2.0;
	this->stop_win = this->rng->next_f64(0.05, 0.20);
}

void trader::NormalTraderAgent::on_cycle(exchange::ExchangeApi &api) {
	this->adjust_profiles_with_events(api);
	this->adjust_profiles_with_price_data(api);

	this->negotiate_orders(api);
	this->sell_stocks(api);
	this->buy_up_stocks(api);
	this->had_cycle = true;
}

void trader::NormalTraderAgent::init(trader::TraderAgentInitPayload payload) {
	TraderAgent::init(payload);

	for (usize ii = 0; ii < payload.companies->size(); ii++) {
		auto el = payload.companies->at(ii);
		this->company_profiles.push_back(TraderCompanyProfile{
				el->get_id(),
				this->get_fundamentals(el),
				0,
				0,
				0,
		});
	}

	this->position_count = std::min(this->position_count, payload.companies->size());
}

f64 trader::NormalTraderAgent::get_fundamentals(const Rc<Company> &cmp) {
	const auto base_rk = this->leadership_bias + this->finance_bias + this->focus_sector_threshold;

	auto sector_bias = std::abs(cmp->get_sector() - this->sector_focus) * this->focus_sector_threshold;
	auto lds = cmp->get_leadership() * this->leadership_bias;
	auto fns = cmp->get_financials() * this->finance_bias;
	return (lds + fns + sector_bias) / base_rk;
}

void trader::NormalTraderAgent::buy_up_stocks(ExchangeApi &api) {
	auto positions = api.get_owned_stocks();
	auto target_pos_count = (usize) std::max((int) this->position_count - (int) positions.size(), 0);

	for (usize ii = 0; ii < target_pos_count; ++ii) {
		this->buy_one_stock(api);
	}
}

void trader::NormalTraderAgent::buy_one_stock(ExchangeApi &api) {
	auto cmp = this->choose_company_to_buy(api);
	if (!cmp) {
		return;
	}
	auto cmp_prof = this->company_profiles.find([&cmp](Rc<TraderCompanyProfile> prof) {
		return prof->company_id == cmp->get_id();
	});

	if (!cmp_prof) {
		return;
	}

	auto worth =
			this->get_per_stock_spending(api.get_trader_available_balance()) * (1 + this->rng->next_f64(0, 0.2) - 0.1);
	auto base_pr = cmp->get_stock_price();
	auto adjusted_negotiation_pr = (usize) (base_pr *
											(1 - NormalTraderAgent::negotiation_percentage(cmp_prof->sentiment, 0)));
	auto price_per_share = std::max(adjusted_negotiation_pr, (usize) 1);
	auto shares = (usize) std::floor(worth / price_per_share);

	if (shares < 1) {
		return;
	}

	if (shares * price_per_share > api.get_trader_available_balance()) {
		return;
	}

	// api.get_cli()->os() << "T opening Buy: " << this->get_id() <<", " << shares << " symb: "<< cmp->get_symbol();
	// api.get_cli()->print_ln();

	api.open_order(exchange::OrderCreationPayload{
			exchange::OrderType::Buy,
			cmp->get_id(),
			shares,
			price_per_share,
			Option<usize>()
	});
}

Rc<Company> trader::NormalTraderAgent::choose_company_to_buy(ExchangeApi &api) {
	auto positions = api.get_owned_stocks();
	auto sorted_profiles = this->company_profiles.sort_by([](Rc<TraderCompanyProfile> aa, Rc<TraderCompanyProfile> bb) {
		return aa->sentiment > bb->sentiment;
	});

	auto at_profile = (usize) 0;
	auto market = api.get_market_context();
	auto company_chosen = nhflib::make_rc<Company>();

	while (true) {
		if (at_profile == sorted_profiles.size() || company_chosen) {
			break;
		}

		auto profile = sorted_profiles.at(at_profile);
		auto comp = market.companies->find([&profile](Rc<Company> cmp) {
			return cmp->get_id() == profile->company_id;
		});

		auto has_pos = positions.some([&profile](Rc<TraderStock> stc) {
			return stc->company_id == profile->company_id;
		});
		auto has_open_order = api.get_orders().some([&profile](Rc<Order> ord) {
			return ord->company_id == profile->company_id;
		});

		auto can_afford =
				comp->get_ask().unwrap_or(0) >= this->get_per_stock_spending(api.get_trader_available_balance());

		if (has_pos || has_open_order || !comp->get_had_an_ipo() || can_afford) {
			at_profile++;
			continue;
		}

		company_chosen = comp;
	}

	return company_chosen;
}

bool trader::NormalTraderAgent::is_retail() const {
	return true;
}

void trader::NormalTraderAgent::adjust_profiles_with_events(ExchangeApi &api) {
	auto evs = api.get_unseen_events();

	for (auto ev: evs) {
		if (ev->target == event::EventTarget::Global) {
			this->adjust_with_global_event(ev);
		} else if (ev->target == event::EventTarget::Sector) {
			this->adjust_with_sector(api, ev);
		} else {
			this->adjust_with_company(api, ev);
		}
	}
}

void trader::NormalTraderAgent::adjust_with_global_event(Rc<Event> event) {
	for (auto prof : this->company_profiles) {
		auto sent_diff = this->get_event_personal_take(event);

		prof->sentiment += sent_diff;
	}
}

void trader::NormalTraderAgent::adjust_with_sector(ExchangeApi &api, Rc<Event> event) {
	auto companies = api.get_market_context().companies;

	for (auto prof : this->company_profiles) {
		auto cmp = companies->find([&prof](Rc<Company> aa) {
			return aa->get_id() == prof->company_id;
		});

		auto sent_diff = this->get_event_personal_take(event);
		auto sector_diff = 1 - std::abs(cmp->get_sector() - event->sector_target.unwrap_or(0.5));

		prof->sentiment += sent_diff * sector_diff * event->weight;
	}
}

void trader::NormalTraderAgent::adjust_with_company(ExchangeApi &api, Rc<Event> event) {
	auto companies = api.get_market_context().companies;
	auto cmp = companies->find([&event](Rc<Company> aa) {
		return aa->get_id() == event->company_target.unwrap_or(0);
	});

	auto cmp_prof = this->company_profiles.find([&cmp](Rc<TraderCompanyProfile> prof) {
		return prof->company_id == cmp->get_id();
	});
	if (!cmp_prof) {
		return;
	}

	auto sent_diff = this->get_event_personal_take(event) * event->weight * event->weight;
	cmp_prof->sentiment += sent_diff;
}

f64 trader::NormalTraderAgent::get_event_personal_take(Rc<Event> event) const {
	return event->sentiment * event->weight * std::abs(this->nonce_focus - event->nonce);
}

void trader::NormalTraderAgent::adjust_profiles_with_price_data(ExchangeApi &api) {
	auto companies = api.get_market_context().companies;

	for (auto profile : this->company_profiles) {
		auto cmp = companies->find([&profile](Rc<Company> cmp) {
			return cmp->get_id() == profile->company_id;
		});

		auto buy_change = (int) cmp->get_buy_vol() - (int) profile->last_buy_vol;
		auto sell_change = (int) cmp->get_sel_vol() - (int) profile->last_sell_vol;

		auto pos_delta = (buy_change > 0 ? buy_change : 0) + (sell_change < 0 ? -sell_change : 0);
		auto neg_delta = std::abs(buy_change) + std::abs(sell_change) - pos_delta;
		auto vol = (profile->last_buy_vol + profile->last_sell_vol);
		auto vol_safe = (vol == 0 ? 1 : vol);

		auto pos_diff = pos_delta / vol_safe;
		auto neg_diff = neg_delta / vol_safe;
		auto price_diff = ((int) cmp->get_stock_price() - (int) profile->last_price) / (f64) (profile->last_price);

		if (this->had_cycle) {
			profile->sentiment += pos_diff * this->volume_sensitivity;
			profile->sentiment += neg_diff * this->volume_sensitivity;
			profile->sentiment += price_diff * this->price_sensitivity;
		}

		profile->last_sell_vol = cmp->get_sel_vol();
		profile->last_buy_vol = cmp->get_buy_vol();
		profile->last_price = cmp->get_stock_price();
	}
}

usize trader::NormalTraderAgent::get_per_stock_spending(usize balance) const {
	return (usize) ((1.0 / this->position_count) * balance);
}

void trader::NormalTraderAgent::sell_stocks(ExchangeApi &api) {
	auto portfolio = api.get_owned_stocks();
	auto companies = api.get_market_context().companies;
	auto orders = api.get_orders();

	for (auto stock : portfolio) {
		auto profile = this->company_profiles.find([&stock](Rc<TraderCompanyProfile> prof) {
			return stock->company_id == prof->company_id;
		});
		auto cmp = companies->find([&stock](Rc<Company> cmp) {
			return cmp->get_id() == stock->company_id;
		});
		auto order_for_comp = orders.find([&stock](Rc<Order> cmp) {
			return cmp->company_id == stock->company_id;
		});

		if (!profile || order_for_comp) {
			continue;
		}
		auto bias = this->bought_bias * this->get_fundamentals(cmp);
		auto stop_loss_s = -(bias + this->stop_loss);
		auto stop_win_ws = bias + this->stop_win;
		auto price = cmp->get_stock_price();

		auto profit = stock->bought_for / (f64) (price == 0 ? 1 : price) - 1;

		if (profit > stop_loss_s && profit < stop_win_ws) {
			continue;
		}

		auto price_per_share = (usize) ((NormalTraderAgent::negotiation_percentage(profile->sentiment, 0) + 1) *
										cmp->get_ask().unwrap_or(0));
		// api.get_cli()->os() << "T opening Sell: " << this->get_id() <<", " << stock->amount << " symb: "<< cmp->get_symbol() << ", for/sh: "<< utils::format_money(price_per_share);
		// api.get_cli()->print_ln();

		api.open_order(exchange::OrderCreationPayload{
				exchange::OrderType::Sell,
				cmp->get_id(),
				stock->free_amount,
				price_per_share,
				Option<usize>()
		});
	}
}

f64 trader::NormalTraderAgent::negotiation_percentage(f64 sentiment, usize time) {
	auto senti_norm = std::min(std::max(sentiment, -1.0), 1.0);
	auto pp = (0.1 * senti_norm) / (time + 1);
	return pp >= 0.01 ? pp : 0;
}

void trader::NormalTraderAgent::negotiate_orders(ExchangeApi &api) {
	auto orders = api.get_orders().clone();
	auto companies = api.get_market_context().companies;

	for (auto ord: orders) {
		auto negot = this->negotiations.find([&ord](Rc<OrderNegotiation> nn) {
			return nn->order_id == ord->id;
		});

		auto cmp = companies->find([&ord](Rc<Company> cmp) {
			return cmp->get_id() == ord->company_id;
		});

		auto profile = company_profiles.find([&ord](Rc<TraderCompanyProfile> prof) {
			return prof->company_id == ord->company_id;
		});

		if (!cmp || !profile) {
			continue;;
		}

		if (!negot) {
			OrderNegotiation nn{
					ord->id,
					0
			};
			negot = nhflib::make_rc(nn);
			this->negotiations.push_back(negot);
		}
		auto new_price = ord->target_price;

		if (ord->type == exchange::OrderType::Buy) {
			auto base_pr = cmp->get_bid().unwrap_or(0);
			auto adjusted_negotiation_pr = (usize) (base_pr * (1 - NormalTraderAgent::negotiation_percentage(
					profile->sentiment, negot->times)));
			new_price = std::max(adjusted_negotiation_pr, (usize) 1);
		} else {
			new_price = (usize) ((NormalTraderAgent::negotiation_percentage(profile->sentiment, negot->times) + 1) *
								 cmp->get_ask().unwrap_or(0));
		}

		exchange::OrderCreationPayload new_ord{
				ord->type,
				ord->company_id,
				ord->amount,
				new_price,
				Option<usize>(),
		};
		api.cancel_order(ord->id);

		if (api.get_trader_available_balance() >= new_ord.get_total_price()) {
			auto oo = api.open_order(new_ord);
			negot->order_id = oo.id;
			negot->times++;
		} else {
			this->negotiations.filter_in_place([&negot](Rc<OrderNegotiation> nn){
				return nn->order_id != negot->order_id;
			});
		}
	}
}

