#pragma once
#include "../../lib/collections/Vector.h"
#include "../company/Company.h"
#include "./exchange_api/TraderRecordInExchange.h"
#include "ExchangeConfig.h"
using company::Company;

namespace exchange {
	class Exchange {
	private:
		const ExchangeConfig config;
		nhflib::Vector<Company> companies;
		nhflib::Vector<TraderRecordInExchange> traders;
	public:
		Exchange(const ExchangeConfig& config, nhflib::Vector<Company>& companies, nhflib::Vector<ITrader>& traders);
	};
}
