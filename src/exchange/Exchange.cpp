#include "Exchange.h"

#include <utility>
#include "../../lib/types.h"
#include "../../lib/algorithms.h"

using nhflib::Rc;
using nhflib::Vector;

exchange::Exchange::Exchange(const Rc<nhflib::RandomProvider> &rng,
							 const Rc<exchange::ExchangeConfig> &config,
							 const Rc<Vector<Rc<Company>>> &companies,
							 const Rc<Vector<Rc<TraderAgent>>> &traders) {
	this->rng = rng;
	this->config = config;
	this->companies = companies;

	usize median_cash = this->config->get_median_starting_cash();

	std::cout << "Generating Trader Records:" << std::endl;
	auto local_rng = this->rng;

	this->traders = nhflib::make_rc(nhfalgo::map<Rc<TraderAgent>, Rc<TraderRecordInExchange>>(*traders, [&local_rng, &median_cash](
			const Rc<TraderAgent> &trader) {
		usize cash = local_rng->next_usize_normal(0, median_cash * 2, median_cash, median_cash * 0.5);
		usize income = local_rng->next_usize_normal(cash * 0.10, cash * 1.5, cash * 0.3, cash * 0.20);

		TraderRecordInExchange rec(0, trader, cash, income);
		rec.print_debug(std::cout);
		return nhflib::make_rc(rec);
	}));
}

void exchange::Exchange::cycle() {
	this->cycle_count++;

	this->handle_fixed_income_on_cycle();
}

void exchange::Exchange::handle_fixed_income_on_cycle() {
	if (this->cycle_count % this->config->get_fixed_income_interval() != 0) {
		return;
	}

	for (auto &trader_rec : *this->traders) {
		trader_rec->cash_balance += trader_rec->fixed_income;
	}
}
