#pragma once

#include "../../lib/memory/Rc.h"
#include "../../lib/rand/RandomProvider.h"
#include "TraderAgent.h"

namespace trader {
	class TraderAgentBuilder {
		nhflib::Rc<nhflib::RandomProvider> rng;
	public:
		nhflib::Rc<TraderAgent> build_random();
	};
}