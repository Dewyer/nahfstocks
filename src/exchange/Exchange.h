#pragma once

#include "../../lib/collections/Vector.h"
#include "../../lib/memory/Rc.h"
#include "../../lib/rand/RandomProvider.h"
#include "../company/Company.h"
#include "./exchange_api/TraderRecordInExchange.h"

#include "ExchangeConfig.h"

using company::Company;
using nhflib::Rc;
using nhflib::Vector;

namespace exchange {
	class Exchange {
	private:
		Rc<nhflib::RandomProvider> rng;
		Rc<ExchangeConfig> config;
		Rc<Vector<Rc<Company>>> companies;
		Rc<Vector<Rc<TraderRecordInExchange>>> traders;

		usize cycle_count;

		void handle_fixed_income_on_cycle();
	public:
		Exchange(const Rc<nhflib::RandomProvider> &rng,
				 const Rc<exchange::ExchangeConfig> &config,
				 const Rc<Vector<Rc<Company>>> &companies,
				 const Rc<Vector<Rc<TraderAgent>>> &traders);

		void cycle();
	};
}
