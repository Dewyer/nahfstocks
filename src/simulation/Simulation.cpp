#include "Simulation.h"
#include "../exchange/ExchangeBuilder.h"
#include "../../lib/option/Option.h"

simulation::Simulation::Simulation() {
	this->setup();
}

void simulation::Simulation::setup() {
	std::cout << "Building, World!" << std::endl;

	nhflib::Option<usize> seed;
	nhflib::RandomProvider rng_base(seed);
	this->rng = nhflib::make_rc(rng_base);

	Rc<ExchangeConfig> config;

	exchange::ExchangeBuilder exchange_builder(this->rng, config);

	this->exchange = nhflib::make_rc(exchange_builder.build_random());
}

void simulation::Simulation::run() {
	for (int ii = 0; ii < 1500; ++ii) {
		this->exchange->cycle();
	}

	std::cout << "End, World!" << std::endl;
}
