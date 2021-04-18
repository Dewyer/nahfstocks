#pragma once

#include "../../lib/collections/Vector.h"
#include "../../lib/memory/Rc.h"
#include "../../lib/option/Option.h"
#include "../../lib/string/String.h"
#include "../../lib/rand/RandomProvider.h"
#include "../company/Company.h"
#include "./exchange_api/TraderRecordInExchange.h"

#include "../config/Config.h"

namespace company {
	class Company;

	class CompanyAgent;
}

using company::Company;
using nhflib::Rc;
using nhflib::Vector;
using nhflib::String;
using nhflib::Option;

namespace exchange {
	class Exchange {
	private:
		Rc<nhflib::RandomProvider> rng;
		Rc<config::Config> config;
		Rc<Vector<Company>> companies;
		Rc<Vector<TraderRecordInExchange>> traders;

		usize cycle_count;
		usize mean_traders_per_cycle;

		usize last_order_id;

		Rc<TraderRecordInExchange> create_trader_record(const Rc<TraderAgent> &trader, usize &trader_id);

		void setup_traders(const Rc<Vector<TraderAgent>> &trader_agents,
						   const Rc<Vector<company::CompanyAgent>> &company_agents);

		void handle_fixed_income_on_cycle();

		void recalculate_prices_on_cycle();

		void handle_trader_agent_activation();

		static void execute_orders(Rc<Order> buy, Rc<Order> sell);

		void clear_executed_orders();

		void execute_open_auction();

	public:
		Exchange(const Rc<nhflib::RandomProvider> &rng,
				 const Rc<config::Config> &config,
				 const Rc<Vector<Company>> &companies,
				 const Rc<Vector<TraderAgent>> &traders,
				 const Rc<Vector<company::CompanyAgent>> &company_agents);

		void cycle();

		static Option<String>
		get_order_validation_error(Rc<TraderRecordInExchange> trader, const exchange::OrderCreationPayload &order);

		exchange::Order open_order(Rc<TraderRecordInExchange> trader, exchange::OrderCreationPayload order);

		void cancel_order(Rc<TraderRecordInExchange> trader, usize order_id);
	};
}
