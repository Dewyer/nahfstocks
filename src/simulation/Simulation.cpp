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

	auto config = nhflib::make_rc_ctr<config::Config>();

	exchange::ExchangeBuilder exchange_builder(this->rng, config);

	this->exchange = exchange_builder.build_random();
}

void simulation::Simulation::run(nhflib::Option<usize> limit_cycles) {

	for (usize ii = 0; ii < limit_cycles.unwrap_or(10); ++ii) {
		this->exchange->cycle();
	}

	std::cout << "End, World!" << std::endl;
}
