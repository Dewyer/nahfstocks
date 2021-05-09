#pragma once
#include "../exchange/Exchange.h"
#include "../../lib/rand/RandomProvider.h"
#include "../../lib/memory/Rc.h"
#include "../../lib/option/Option.h"
#include "../config/Config.h"
#include "../exchange/exchange_api/TraderRecordInExchange.h"
#include "../cli/CliHelper.h"
#include "../events/EventDispatcher.h"

using nhflib::Option;
using nhflib::Rc;
using config::Config;
using nhflib::RandomProvider;
using exchange::Exchange;
using exchange::TraderRecordInExchange;

namespace simulation {
	class Simulation {

		Rc<RandomProvider> rng;
		Rc<Config> config;
		Rc<CliHelper> cli;

		void setup();

	public:
		explicit Simulation(const Rc<Config> &_config, const Rc<CliHelper> &_cli) : config(_config), cli(_cli) {
			this->setup();
		}

		Rc<Exchange> exchange;

		void run_for(usize cycles);

		// void interupt();
	};
}
