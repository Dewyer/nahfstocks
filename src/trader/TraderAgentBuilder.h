#pragma once
#include "../../lib/memory/Rc.h"
#include "../../lib/rand/RandomProvider.h"
#include "TraderAgent.h"

namespace trader {
	class TraderAgentBuilder {
		nhflib::Rc<nhflib::RandomProvider> rng;

	public:
		TraderAgentBuilder(const nhflib::Rc<nhflib::RandomProvider> &_rng) : rng(_rng) {}

		nhflib::Rc<TraderAgent> build_random();
	};
}