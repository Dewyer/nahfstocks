#pragma once

#include "../../lib/memory/Rc.h"
#include "../../lib/rand/RandomProvider.h"
#include "TraderAgent.h"

namespace trader {
	class TraderAgentBuilder {
		nhflib::Rc<nhflib::RandomProvider> rng;
	public:
		TraderAgent build_random();
	};
}