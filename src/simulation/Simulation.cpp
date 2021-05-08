#include "Simulation.h"
#include "../exchange/ExchangeBuilder.h"
#include "../../lib/option/Option.h"

void simulation::Simulation::setup() {
	this->cli->print_ln("Building, World!");

	nhflib::Option<usize> seed;
	nhflib::RandomProvider rng_base(seed);
	this->rng = nhflib::make_rc(rng_base);

	exchange::ExchangeBuilder exchange_builder(this->rng, this->config, this->cli);

	this->exchange = exchange_builder.build_random();
}

void simulation::Simulation::run_for(usize cycles) {
	for (usize ii = 0; ii < cycles; ++ii) {
		this->exchange->cycle();
	}
}
