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

		usize ask_question(const nhflib::String &question, nhflib::Vector<nhflib::String> answers);

		void dump_simulation_data();

		void start_sim(nhflib::Option<usize> limit);

		void show_trader_details(usize trader_id);

		void list_traders();

		void show_company_details(nhflib::String company_symbol);

		void list_companies();

		void show_global_sim_stats();

		void show_start_stop();

		void show_main_menu();

	public:
		SimulationCli() {
			this->config = nhflib::make_rc_ctr<Config>();
		}

		void start();
	};
}

