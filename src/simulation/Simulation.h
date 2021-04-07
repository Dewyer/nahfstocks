#pragma once
#include "../exchange/Exchange.h"
#include "memory"
#include "../../lib/rand/RandomProvider.h"

namespace simulation {
	class Simulation {
		std::shared_ptr<nhflib::RandomProvider> rng;

		std::shared_ptr<exchange::Exchange> exchange;
	public:
		Simulation();
	};
}
