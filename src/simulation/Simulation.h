#pragma once

#include "../exchange/Exchange.h"
#include "memory"
#include "../../lib/rand/RandomProvider.h"
#include "../../lib/memory/Rc.h"
#include "../../lib/option/Option.h"
#include "../config/Config.h"

using nhflib::Rc;
using config::Config;

namespace simulation {
	class Simulation {

		Rc<nhflib::RandomProvider> rng;
		Rc<Config> config;

		void setup();

	public:
		explicit Simulation(const Rc<Config> &_config) : config(_config) {
			this->setup();
		}

		Rc<exchange::Exchange> exchange;

		void run(nhflib::Option<usize> limit_cycles);

		// void interupt();
	};
}
