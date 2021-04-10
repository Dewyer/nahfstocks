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
		ExchangeConfig config;

	public:
		explicit ExchangeBuilder(const nhflib::Rc<RandomProvider>& _rng, ExchangeConfig _config) {
			this->rng = _rng;
			this->config = _config;
		}

		Exchange build_random();
	};

}