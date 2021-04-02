#include "Exchange.h"

#include <utility>
#include "../../lib/types.h"

exchange::Exchange::Exchange(exchange::ExchangeConfig config, nhflib::Vector<Company> &companies,
                             nhflib::Vector<ITrader> &traders) : config(std::move(config)) {
    this->companies = companies;
    for (usize ii = 0; ii < traders.size(); ++ii) {
        // TraderRecordInExchange rec(, this->config.starting_cash.unwrap());
        // this->traders.push_back(rec);
    }
}
