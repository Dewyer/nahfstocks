#pragma once

#include "../../lib/collections/Vector.h"
#include "../../lib/memory/Rc.h"
#include "../../lib/rand/RandomProvider.h"
#include "../company/Company.h"
#include "./exchange_api/TraderRecordInExchange.h"

#include "../config/Config.h"

namespace company {
	class Company;
}

using company::Company;
using nhflib::Rc;
using nhflib::Vector;

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

		void handle_fixed_income_on_cycle();

		void handle_trader_agent_activation();

		void execute_orders(Rc<Order> buy, Rc<Order> sell);

		void clear_executed_orders();

		void execute_open_auction();
	public:
		Exchange(const Rc<nhflib::RandomProvider> &rng,
				 const Rc<config::Config> &config,
				 const Rc<Vector<Company>> &companies,
				 const Rc<Vector<TraderAgent>> &traders);

		void cycle();

		exchange::Order open_order(Rc<TraderRecordInExchange> trader, exchange::OrderCreationPayload order);

		void cancel_order(Rc<TraderRecordInExchange> trader, usize order_id);
	};
}
