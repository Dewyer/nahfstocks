#include "Simulation.h"
#include "../exchange/ExchangeBuilder.h"
#include "../../lib/option/Option.h"

void simulation::Simulation::setup() {
	std::cout << "Building, World!" << std::endl;

	nhflib::Option<usize> seed;
	nhflib::RandomProvider rng_base(seed);
	this->rng = nhflib::make_rc(rng_base);

	exchange::ExchangeBuilder exchange_builder(this->rng, this->config);

	this->exchange = exchange_builder.build_random();
}

void simulation::Simulation::run(nhflib::Option<usize> limit_cycles) {

	for (usize ii = 0; ii < limit_cycles.unwrap_or(10); ++ii) {
		this->exchange->cycle();
	}

	std::cout << "End, World!" << std::endl;
}
