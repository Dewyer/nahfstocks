#include "Exchange.h"

namespace exchange {



};

exchange::Exchange::Exchange(const exchange::ExchangeConfig &config, nhflib::Vector<Company> &companies,
							 nhflib::Vector<ITrader> &traders): config(config) {
	this->companies = companies;
}
