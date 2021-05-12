#pragma once

#include "../../lib/memory/Rc.h"
#include "../../lib/rand/RandomProvider.h"
#include "../config/Config.h"
#include "TraderAgent.h"

namespace trader {

	/// Builds the default TraderAgent for an exchange
	class TraderAgentBuilder {
		nhflib::Rc<nhflib::RandomProvider> rng;
		nhflib::Rc<config::Config> config;
	public:
		TraderAgentBuilder(const nhflib::Rc<nhflib::RandomProvider> &_rng, const nhflib::Rc<config::Config> _config)
				: rng(_rng), config(_config) {}

		nhflib::Rc<TraderAgent> build_random();
	};
}