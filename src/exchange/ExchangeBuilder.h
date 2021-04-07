#pragma once
#include <memory>
#include <utility>
#include "../../lib/rand/RandomProvider.h"
#include "./Exchange.h"

using nhflib::RandomProvider;
using exchange::Exchange;
using exchange::ExchangeConfig;

namespace exchange {

	class ExchangeBuilder {
		std::shared_ptr<RandomProvider> rng;
		ExchangeConfig config;

	public:
		explicit ExchangeBuilder(std::shared_ptr<RandomProvider> _rng, ExchangeConfig _config) {
			this->rng = std::move(_rng);
			this->config = std::move(_config);
		}

		Exchange build_random();
	};

}