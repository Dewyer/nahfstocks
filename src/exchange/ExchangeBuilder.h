#pragma once

#include <utility>
#include "../../lib/rand/RandomProvider.h"
#include "../../lib/memory/Rc.h"
#include "./Exchange.h"

using nhflib::RandomProvider;
using exchange::Exchange;
using exchange::ExchangeConfig;

namespace exchange {

	class ExchangeBuilder {
		nhflib::Rc<RandomProvider> rng;
		nhflib::Rc<ExchangeConfig> config;

	private:
		Vector<Company> build_companies();

		Vector<TraderAgent> build_trader_agents();

	public:
		explicit ExchangeBuilder(const nhflib::Rc<RandomProvider> &_rng,const nhflib::Rc<ExchangeConfig>& _config) {
			this->rng = _rng;
			this->config = _config;
		}

		Exchange build_random();
	};

}