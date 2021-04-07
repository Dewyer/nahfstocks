#include "Exchange.h"

#include <utility>
#include "../../lib/types.h"

exchange::Exchange::Exchange(std::shared_ptr<nhflib::RandomProvider> rng,exchange::ExchangeConfig config, nhflib::Vector<Company> &companies,
                             nhflib::Vector<ITrader> &traders) {
	this->rng = std::move(rng);
	this->config = config;
    this->companies = companies;

    usize median_cash = this->config.get_median_starting_cash();

    for (auto & trader : traders) {
    	usize cash = this->rng->next_usize_normal(0, median_cash*2, median_cash, median_cash*0.5);
        TraderRecordInExchange rec(trader, cash);
        this->traders.push_back(rec);
    }
}
