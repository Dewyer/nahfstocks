#pragma once
#include "../../lib/collections/Vector.h"
#include "../../lib/memory/Rc.h"
#include "../../lib/option/Option.h"
#include "../../lib/string/String.h"
#include "../../lib/rand/RandomProvider.h"
#include "../company/Company.h"
#include "./exchange_api/TraderRecordInExchange.h"
#include "../../tests/exchange/exchange_tests.h"
#include "./ExchangeStats.h"
#include "../cli/CliHelper.h"
#include "../config/Config.h"
#include "../events/EventDispatcher.h"
#include "../events/Event.h"

namespace company {
	class Company;

	class CompanyAgent;
}

using cli::CliHelper;
using company::Company;
using config::Config;
using nhflib::Rc;
using nhflib::Vector;
using nhflib::String;
using nhflib::Option;
using nhflib::RandomProvider;
using event::Event;
using event::EventDispatcher;

namespace exchange {
	class Exchange {
	private:
		Rc<RandomProvider> rng;
		Rc<Config> config;
		Rc<Vector<Company>> companies;
		Rc<Vector<TraderRecordInExchange>> traders;
		Rc<CliHelper> cli;
		Rc<EventDispatcher> event_dispatcher;

		usize cycle_count;
		usize mean_traders_per_cycle;

		usize last_order_id;

		bool runtime_exception_occured;

		Rc<TraderRecordInExchange> create_trader_record(const Rc<TraderAgent> &trader, usize &trader_id);

		void setup_traders(const Rc<Vector<TraderAgent>> &trader_agents,
						   const Rc<Vector<company::CompanyAgent>> &company_agents);

		void init_traders();

		void handle_event_generation();

		void handle_company_price_sampling();

		void handle_fixed_income_on_cycle();

		void recalculate_prices_on_cycle();

		void handle_trader_agent_activation();

		static void execute_orders(Rc<Order> buy, Rc<Order> sell);

		void clear_executed_orders();

		void execute_open_auction();

		Rc<Company> get_biggest_company();

		Rc<TraderRecordInExchange> get_richest_trader();

	public:
		Exchange(const Rc<nhflib::RandomProvider> &rng,
				 const Rc<config::Config> &config,
				 const Rc<Vector<Company>> &companies,
				 const Rc<Vector<TraderAgent>> &traders,
				 const Rc<Vector<company::CompanyAgent>> &company_agents,
				 const Rc<CliHelper> &_cli);

		void cycle();

		usize get_cycle_count() const noexcept {
			return this->cycle_count;
		}

		const Rc<Vector<TraderRecordInExchange>> &get_trader_records() const {
			return this->traders;
		}

		Rc<Vector<Company>> &get_companies() {
			return this->companies;
		}

		ExchangeStats get_stats();

		static Option<String>
		get_order_validation_error(Rc<TraderRecordInExchange> trader, const exchange::OrderCreationPayload &order);

		exchange::Order open_order(Rc<TraderRecordInExchange> trader, exchange::OrderCreationPayload order);

		void cancel_order(Rc<TraderRecordInExchange> trader, usize order_id);

		friend ExchangeTester;
	};
}
