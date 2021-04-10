#pragma once

#include "../exchange/Exchange.h"
#include "memory"
#include "../../lib/rand/RandomProvider.h"
#include "../../lib/memory/Rc.h"

namespace simulation {
	class Simulation {
		nhflib::Rc<nhflib::RandomProvider> rng;

		nhflib::Rc<exchange::Exchange> exchange;

		void setup();
	public:
		Simulation();

		void run();
	};
}
