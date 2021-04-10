#include "Exchange.h"

#include <utility>
#include "../../lib/types.h"

exchange::Exchange::Exchange(const nhflib::Rc<nhflib::RandomProvider>& rng,exchange::ExchangeConfig config, nhflib::Vector<Company> &companies,
                             nhflib::Vector<Trader> &traders) {
	this->rng = rng;
	this->config = config;
    this->companies = companies;

    usize median_cash = this->config.get_median_starting_cash();

    for (auto & trader : traders) {
    	usize cash = this->rng->next_usize_normal(0, median_cash*2, median_cash, median_cash*0.5);
        TraderRecordInExchange rec(Rc<Trader>::make_rc(trader), cash);
        this->traders.push_back(rec);
    }
}
