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


	public:
		Exchange(const nhflib::Rc<nhflib::RandomProvider> &rng, const nhflib::Rc<ExchangeConfig>& config,
				 nhflib::Vector<Company> &companies, nhflib::Vector<TraderAgent> &traders);
	};
}
