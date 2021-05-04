#include "SimulationCli.h"
#include "./CliQuestioner.h"

void cli::SimulationCli::start() {
	try {
		this->config->read_config();
		this->show_startup_screen();

		if (this->config->get_is_interactive()) {
			this->start_interactive();
		} else {
			this->cli->print_ln("TO Impl. non interactive");
		}

		// this->sim = nhflib::make_rc(Simulation(this->config));
		// this->sim->run(Option<usize>(100));
	} catch (std::runtime_error &err) {
		std::cout << "Runtime error: " << err.what() << std::endl;
	}
}

void cli::SimulationCli::show_startup_screen() {
	this->cli->print_ln("Nahfstocks ! - Stock Simulation");
}

void cli::SimulationCli::start_interactive() {
	while (true) {
		auto should_quit = this->show_main_menu();
		if (should_quit) {
			break;
		}
	}

	this->cli->print_ln("Simulation over - good bye");
}

bool cli::SimulationCli::show_main_menu() {
	const auto exit_ans = 2;
	auto menu_ans = this->cli->build_question()
			.question("Menu")
			.option("Stats")
			.option("Exit")
			.ask();
	if (!menu_ans || menu_ans.unwrap() == exit_ans) {
		return true;
	}

	switch (menu_ans.unwrap()) {
		case 1:
			this->show_simulation_stats();
			break;
	}

	return false;
}

void cli::SimulationCli::show_simulation_stats() {
	this->cli->print_ln("Simulation stats:");
	this->cli->os() << "\t Cylces: " << 0;
	this->cli->print_ln();
}
