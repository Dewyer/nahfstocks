#include "Simulation.h"
#include "../exchange/ExchangeBuilder.h"
#include "../../lib/option/Option.h"

simulation::Simulation::Simulation() {
	std::cout << "Building, World!" << std::endl;

	nhflib::Option<usize> seed;
	nhflib::RandomProvider rng_base(seed);
	this->rng = Rc<nhflib::RandomProvider>::make_rc(rng_base);

	Rc<ExchangeConfig> config;

	exchange::ExchangeBuilder exchange_builder(this->rng, config);

	this->exchange = Rc<exchange::Exchange>::make_rc(exchange_builder.build_random());
}
