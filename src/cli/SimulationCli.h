#pragma once

#include "../simulation/Simulation.h"
#include "../../lib/option/Option.h"
#include "../../lib/string/String.h"
#include "../../lib/collections/Vector.h"
#include "../config/Config.h"

using config::Config;
using simulation::Simulation;

namespace cli {
	class SimulationCli {
		Rc<Simulation> sim;
		Rc<Config> config;
		Rc<CliHelper> cli;

		void dump_simulation_data();

		void start_sim(nhflib::Option<usize> limit);

		template<typename T>
		void show_list_of_printables(const Rc<Vector<T>>& to_list, const String& what) {
			this->cli->os() << "All (" << to_list->size() << ") " << what << ":";
			this->cli->print_ln();

			this->cli->set_tabs(1);

			for (usize ii = 0; ii < to_list->size(); ii++) {
				auto tt = to_list->at(ii);
				tt->print_to(this->cli);
			}

			this->cli->clear_tabs();
		}

		void show_list_of_companies();

		void show_list_of_traders();

		void show_start_stop();

		void show_simulation_stats();

		bool show_main_menu();

		void show_startup_screen();

		void show_trader_details();

		void show_trader_details_by_id(usize trader_id);

		void show_company_details();

		void show_company_details_by_symbol(nhflib::String company_symbol);

		void start_interactive();

	public:
		SimulationCli() {
			this->config = nhflib::make_rc_ctr<Config>();
			this->cli = nhflib::make_rc(this->config->should_log() ? CliHelper(&std::cout) : CliHelper(nullptr));
		}

		void start();
	};
}

