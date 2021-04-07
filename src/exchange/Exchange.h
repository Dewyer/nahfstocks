#pragma once

#include "../../lib/collections/Vector.h"
#include "../../lib/rand/RandomProvider.h"
#include "../company/Company.h"
#include "./exchange_api/TraderRecordInExchange.h"
#include "ExchangeConfig.h"

using company::Company;

namespace exchange {
    class Exchange {
    private:
		std::shared_ptr<nhflib::RandomProvider> rng;
		ExchangeConfig config;
        nhflib::Vector<Company> companies;
        nhflib::Vector<TraderRecordInExchange> traders;


    public:
        Exchange(std::shared_ptr<nhflib::RandomProvider> rng,ExchangeConfig config, nhflib::Vector<Company> &companies, nhflib::Vector<ITrader> &traders);
    };
}
