#include "SimulationCli.h"
#include "./CliQuestioner.h"
#include "../utils/format_money.h"

void cli::SimulationCli::start() {
	try {
		this->config->read_config();
		this->show_startup_screen();

		this->sim = nhflib::make_rc(Simulation(this->config, this->cli));

		if (this->config->get_is_interactive()) {
			this->start_interactive();
		} else {
			this->cli->print_ln("TO Impl. non interactive");
		}

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
	const auto exit_ans = 6;
	auto menu_ans = this->cli->build_question()
			.question("Menu")
			.option("Statistics")
			.option("List companies")
			.option("List trader records")
			.option("Trader's details")
			.option("Company's details")
			.option("Exit")
			.ask();
	if (!menu_ans || menu_ans.unwrap() == exit_ans) {
		return true;
	}

	switch (menu_ans.unwrap()) {
		case 1:
			this->show_simulation_stats();
			break;
		case 2:
			this->show_list_of_companies();
			break;
		case 3:
			this->show_list_of_traders();
			break;
		case 4:
			this->show_trader_details();
			break;
		case 5:
			this->show_company_details();
			break;
	}

	return false;
}

void cli::SimulationCli::show_simulation_stats() {
	auto stats = this->sim->exchange->get_stats();

	this->cli->print_ln("Simulation stats:");
	this->cli->set_tabs(1);

	this->cli->os() << "Cylces: " << stats.get_at_cycles();
	this->cli->print_ln();
	this->cli->os() << "Total Money: " << utils::format_money(stats.get_total_money());
	this->cli->print_ln();

	this->cli->print_ln("Biggest company: ");
	this->cli->set_tabs(2);
	stats.get_biggest_company()->print_to(this->cli);
	this->cli->print_ln();

	this->cli->set_tabs(1);
	this->cli->print_ln("Richest trader: ");
	this->cli->set_tabs(2);

	stats.get_richest_trader()->print_to(this->cli);
	this->cli->print_ln();
	this->cli->clear_tabs();
}

void cli::SimulationCli::show_list_of_companies() {
	this->show_list_of_printables(this->sim->exchange->get_companies(), "companies");
}

void cli::SimulationCli::show_list_of_traders() {
	this->show_list_of_printables(this->sim->exchange->get_trader_records(), "traders");
}

void cli::SimulationCli::show_trader_details_by_id(usize trader_id) {
	auto traders = this->sim->exchange->get_trader_records();
	auto trader = traders->find([&trader_id](Rc<TraderRecordInExchange> trader_rec){
		return trader_rec->trader_id == trader_id;
	});

	if (!trader) {
		this->cli->print_ln("Trader with the given id doesn't exist.");
		return;
	}

	this->cli->set_tabs(1);
	trader->print_to(this->cli);
	this->cli->clear_tabs();
}

void cli::SimulationCli::show_trader_details() {
	this->cli->os() << "Enter the trader's id (0.." << this->sim->exchange->get_trader_records()->size() <<"): ";
	auto id = this->cli->read_safe_inst<usize>();
	this->cli->print_ln();

	if (!id) {
		this->cli->print_ln("Invalid input given.");
		return;
	}

	this->show_trader_details_by_id(id.unwrap());
}

void cli::SimulationCli::show_company_details() {
	this->cli->os() << "Enter the company's symbol: ";
	auto symbol = this->cli->read_safe_inst<String>();
	this->cli->print_ln();

	if (!symbol) {
		this->cli->print_ln("Invalid input given.");
		return;
	}

	this->show_company_details_by_symbol(symbol.unwrap());
}

void cli::SimulationCli::show_company_details_by_symbol(nhflib::String company_symbol) {
	auto companies = this->sim->exchange->get_companies();
	auto company = companies->find([&company_symbol](Rc<Company> cmp){
		return cmp->get_symbol() == company_symbol;
	});

	if (!company) {
		this->cli->print_ln("Company with given symbol doesn't exist.");
		return;
	}

	this->cli->set_tabs(1);
	company->print_to(this->cli);
	this->cli->clear_tabs();
}
