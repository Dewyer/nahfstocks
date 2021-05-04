#include "SimulationCli.h"

void cli::SimulationCli::start() {
	try {
		this->config->read_config();
		std::cout << this->config->get_seed().unwrap_or(11);
		// this->sim = nhflib::make_rc(Simulation(this->config));
		// this->sim->run(Option<usize>(100));
	} catch (std::runtime_error &err) {
		std::cout << "Runtime error: " << err.what() << std::endl;
	}
}
