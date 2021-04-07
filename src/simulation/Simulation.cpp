#include "Simulation.h"
#include "../exchange/ExchangeBuilder.h"
#include "../../lib/option/Option.h"

simulation::Simulation::Simulation() {
	std::cout << "Building, World!" << std::endl;

	nhflib::Option<usize> seed;
	nhflib::RandomProvider rng_base(seed);
	this->rng = std::make_shared<nhflib::RandomProvider>(rng_base);

	ExchangeConfig config;

	exchange::ExchangeBuilder exchange_builder(this->rng, config);

	this->exchange = std::make_shared<exchange::Exchange>(exchange_builder.build_random());
}
