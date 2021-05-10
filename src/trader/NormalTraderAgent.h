#pragma once
#include "./TraderAgent.h"
#include "../../lib/memory/Rc.h"
#include "../../lib/collections/Vector.h"
#include "../../lib/string/String.h"
#include "../../lib/rand/RandomProvider.h"
#include "../config/Config.h"
#include "../events/Event.h"

using nhflib::String;
using nhflib::RandomProvider;
using config::Config;
using nhflib::Rc;
using exchange::ExchangeApi;
using event::Event;
using event::EventTarget;

namespace trader {
	struct TraderCompanyProfile {
		usize company_id;
		f64 sentiment;

		usize last_price;
		usize last_buy_vol;
		usize last_sell_vol;
	};

	struct OrderNegotiation {
		usize order_id;
		usize times;
	};

	class NormalTraderAgent : public TraderAgent {
		Rc<RandomProvider> rng;
		Rc<Config> config;
		usize position_count;
		f64 finance_bias;
		f64 leadership_bias;
		f64 sector_focus;
		f64 focus_sector_threshold;
		f64 nonce_focus;
		f64 volume_sensitivity;
		f64 price_sensitivity;
		f64 stop_loss;
		f64 bought_bias;
		f64 stop_win;

		bool had_cycle;

		Vector<TraderCompanyProfile> company_profiles;
		Vector<OrderNegotiation> negotiations;

		usize get_per_stock_spending(usize balance) const;

		f64 get_event_personal_take(Rc<Event> event) const;

		void choose_random_settings();

		f64 get_fundamentals(const Rc<Company>& cmp);

		Rc<Company> choose_company_to_buy(ExchangeApi &api);

		void adjust_with_global_event(Rc<Event> event);

		void adjust_with_company(ExchangeApi &api, Rc<Event> event);

		void adjust_with_sector(ExchangeApi &api, Rc<Event> event);

		void adjust_profiles_with_events(ExchangeApi &api);

		void adjust_profiles_with_price_data(ExchangeApi &api);

		void buy_one_stock(ExchangeApi &api);

		void buy_up_stocks(ExchangeApi &api);

		static f64 negotiation_percentage(f64 sentiment, usize time);

		void sell_stocks(ExchangeApi &api);

		void negotiate_orders(ExchangeApi &api);

	public:
		NormalTraderAgent(const String& _name, const Rc<RandomProvider>& _rng, const Rc<Config>& _config): TraderAgent(_name) {
			this->rng = _rng;
			this->config = _config;
			this->company_profiles = Vector<TraderCompanyProfile>();
			this->negotiations = Vector<OrderNegotiation>();

			this->had_cycle = false;
			this->choose_random_settings();
		}

		virtual void init(TraderAgentInitPayload payload) override;

		bool is_retail() const;

		void on_cycle(ExchangeApi &api) override;
	};

}