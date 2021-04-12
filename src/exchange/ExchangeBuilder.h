#pragma once

#include <utility>
#include "../../lib/rand/RandomProvider.h"
#include "../../lib/memory/Rc.h"
#include "./Exchange.h"

using nhflib::RandomProvider;
using nhflib::Rc;
using exchange::Exchange;
using exchange::ExchangeConfig;

namespace exchange {

	class ExchangeBuilder {
		Rc<RandomProvider> rng;
		Rc<ExchangeConfig> config;

	private:
		Rc<Vector<Company>> build_companies();

		Rc<Vector<TraderAgent>> build_trader_agents();

	public:
		explicit ExchangeBuilder(const nhflib::Rc<RandomProvider> &_rng,const nhflib::Rc<ExchangeConfig>& _config) {
			this->rng = _rng;
			this->config = _config;
		}

		Rc<Exchange> build_random();
	};

}