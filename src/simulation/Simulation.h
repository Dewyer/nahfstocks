#pragma once

#include "../exchange/Exchange.h"
#include "memory"
#include "../../lib/rand/RandomProvider.h"
#include "../../lib/memory/Rc.h"
#include "../../lib/option/Option.h"

namespace simulation {
	class Simulation {
		nhflib::Rc<nhflib::RandomProvider> rng;

		void setup();
	public:
		Simulation();

		nhflib::Rc<exchange::Exchange> exchange;

		void run(nhflib::Option<usize> limit_cycles);

		void interupt();
	};
}
