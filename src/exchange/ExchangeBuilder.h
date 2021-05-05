#pragma once

#include <utility>
#include "../../lib/rand/RandomProvider.h"
#include "../../lib/memory/Rc.h"
#include "./Exchange.h"
#include "../config/Config.h"
#include "../company/CompanyAgent.h"
#include "../../tests/exchange/exchange_tests.h"
#include "../cli/CliHelper.h"

using nhflib::RandomProvider;
using nhflib::Rc;
using exchange::Exchange;
using config::Config;
using company::CompanyAgent;
using cli::CliHelper;

namespace exchange {

	class ExchangeBuilder {
		Rc<RandomProvider> rng;
		Rc<Config> config;
		Rc<CliHelper> cli;

	private:
		Rc<Vector<Company>> build_companies();

		Rc<Vector<TraderAgent>> build_trader_agents();

		Rc<Vector<CompanyAgent>> build_trader_agents_for_companies(Rc<Vector<Company>> companies);

	public:
		explicit ExchangeBuilder(const nhflib::Rc<RandomProvider> &_rng, const nhflib::Rc<config::Config> &_config, const Rc<CliHelper>& _cli) {
			this->rng = _rng;
			this->config = _config;
			this->cli = _cli;
		}

		Rc<Exchange> build_random();

		friend ExchangeTester;
	};

}