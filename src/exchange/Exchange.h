#pragma once

#include "../../lib/collections/Vector.h"
#include "../../lib/memory/Rc.h"
#include "../../lib/rand/RandomProvider.h"
#include "../company/Company.h"
#include "./exchange_api/TraderRecordInExchange.h"

#include "ExchangeConfig.h"

using company::Company;

namespace exchange {
	class Exchange {
	private:
		nhflib::Rc<nhflib::RandomProvider> rng;
		nhflib::Rc<ExchangeConfig> config;
		nhflib::Vector<Company> companies;
		nhflib::Vector<TraderRecordInExchange> traders;

		usize cycle_count;

		void handle_fixed_income_on_cycle();
	public:
		Exchange(const nhflib::Rc<nhflib::RandomProvider> &rng, const nhflib::Rc<ExchangeConfig>& config,
				 nhflib::Vector<Company> &companies, nhflib::Vector<TraderAgent> &traders);

		void cycle();
	};
}
