#include "../../lib/prelude.h"
#include "SimulationCli.h"
#include "./CliQuestioner.h"
#include "../utils/format_money.h"
#include "../exchange/exchange_api/TraderRecordInExchange.h"

constexpr bool THREADING_ENABLED =
#ifdef ETHREAD
		true
#else
		false
#endif
;

using exchange::CompanyDto;

void cli::SimulationCli::start() {
	try {
		this->config->read_config();
		this->show_startup_screen();

		this->sim = nhflib::make_rc(Simulation(this->config, this->cli));

		if (this->config->get_is_interactive()) {
			this->start_interactive();
		} else {
			this->sim->run_for(this->config->get_limit_runs());
		}

	} catch (std::runtime_error &err) {
		this->cli->os() << "Runtime error: " << err.what();
		this->cli->print_ln();
	}

	this->dump_simulation_data();
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
	const auto exit_ans = 7;
	auto menu_ans = this->cli->build_question()
			.question("Menu")
			.option("Statistics")
			.option("List companies")
			.option("List trader records")
			.option("Trader's details")
			.option("Company's details")
			.option("Start/Stop Simulation")
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
		case 6:
			this->show_start_stop();
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

	stats.get_richest_trader()->detailed_print_to(this->cli, [this](usize id) {
		return this->company_lookup_fn(id);
	});

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
	auto trader = traders->find([&trader_id](Rc<TraderRecordInExchange> trader_rec) {
		return trader_rec->trader_id == trader_id;
	});

	if (!trader) {
		this->cli->print_ln("Trader with the given id doesn't exist.");
		return;
	}

	this->cli->set_tabs(1);
	trader->detailed_print_to(this->cli, [this](usize id) {
		return this->company_lookup_fn(id);
	});

	this->cli->clear_tabs();
}

void cli::SimulationCli::show_trader_details() {
	this->cli->os() << "Enter the trader's id (0.." << this->sim->exchange->get_trader_records()->size() << "): ";
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
	auto company = companies->find([&company_symbol](Rc<Company> cmp) {
		return cmp->get_symbol() == company_symbol;
	});

	if (!company) {
		this->cli->print_ln("Company with given symbol doesn't exist.");
		return;
	}

	this->cli->set_tabs(1);
	company->detailed_print_to(this->cli);
	this->cli->clear_tabs();
}

void cli::SimulationCli::show_start_stop() {
	auto run_type_qst = this->cli->build_question()
			.question("How do you want to run the simulation ?")
			.cancelable()
			.option("Limit mode (For a specific number of iterations)");

	if (THREADING_ENABLED) {
		run_type_qst.option("Threaded mode (Until user input is given)");
	}

	auto run_type_ans = run_type_qst.ask();
	if (!run_type_ans || run_type_ans.unwrap() == 0) {
		return;
	}

	auto run_type = run_type_ans.unwrap();
	if (run_type == 1) {
		this->run_simulation_in_limit_mode();
	} else {
		this->cli->print_ln("Other modes not implemented!");
	}
}

void cli::SimulationCli::run_simulation_in_limit_mode() {
	this->cli->print_ln("How many iterations do you want to run?: ");
	auto iters = this->cli->read_safe_inst<usize>();
	if (!iters) {
		this->cli->print_ln("Invalid iteration count!");
	}

	auto iters_number = iters.unwrap();
	this->cli->print_ln("Starting running the iterations...");
	this->sim->run_for(iters_number);
	this->cli->print_ln("Running finished.");
}

exchange::CompanyDto cli::SimulationCli::company_lookup_fn(usize company_id) {
	auto cmp = this->sim->exchange->get_companies()->find([&company_id](Rc<Company> cmp) {
		return cmp->get_id() == company_id;
	});
	return cmp ? CompanyDto{
			cmp->get_symbol(),
			cmp->get_name(),
			cmp->get_stock_price()
	} : CompanyDto::empty();
}

void cli::SimulationCli::dump_simulation_data() {
	if (!this->config->should_dump_json()) {
		return;
	}

	this->cli->print_ln("=== COMPANY JSON DUMP");
	this->cli->print_ln("{companies:[");

	auto companies = this->sim->exchange->get_companies();

	for (usize ii = 0; ii < companies->size(); ii++) {
		auto cmp = companies->at(ii);
		cmp->dump_json(this->cli);
		if (ii != companies->size() - 1) {
			this->cli->print_ln(",");
		}
	}

	this->cli->print_ln("]}");
}
