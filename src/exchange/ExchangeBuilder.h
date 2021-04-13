#pragma once

#include <utility>
#include "../../lib/rand/RandomProvider.h"
#include "../../lib/memory/Rc.h"
#include "./Exchange.h"
#include "../config/Config.h"

using nhflib::RandomProvider;
using nhflib::Rc;
using exchange::Exchange;
using config::Config;

namespace exchange {

	class ExchangeBuilder {
		Rc<RandomProvider> rng;
		Rc<config::Config> config;

	private:
		Rc<Vector<Company>> build_companies();

		Rc<Vector<TraderAgent>> build_trader_agents();

	public:
		explicit ExchangeBuilder(const nhflib::Rc<RandomProvider> &_rng,const nhflib::Rc<config::Config>& _config) {
			this->rng = _rng;
			this->config = _config;
		}

		Rc<Exchange> build_random();
	};

}