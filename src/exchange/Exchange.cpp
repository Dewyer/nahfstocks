#include "Exchange.h"

#include <utility>
#include "../../lib/types.h"

exchange::Exchange::Exchange(const nhflib::Rc<nhflib::RandomProvider> &rng, const nhflib::Rc<exchange::ExchangeConfig>& config,
							 nhflib::Vector<Company> &companies,
							 nhflib::Vector<TraderAgent> &traders) {
	this->rng = rng;
	this->config = config;
	this->companies = companies;

	usize median_cash = this->config->get_median_starting_cash();

	std::cout << "Generating Trader Records:" << std::endl;

	for (auto &trader : traders) {
		usize cash = this->rng->next_usize_normal(0, median_cash * 2, median_cash, median_cash * 0.5);
		usize income = this->rng->next_usize_normal(cash*0.10, cash*1.5, cash*0.3, cash * 0.20);

		TraderRecordInExchange rec(0, Rc<TraderAgent>::make_rc(trader), cash, income);
		rec.print_debug(std::cout);
		this->traders.push_back(rec);
	}
}

void exchange::Exchange::cycle() {
	this->cycle_count++;

	this->handle_fixed_income_on_cycle();
}

void exchange::Exchange::handle_fixed_income_on_cycle() {
	if (this->cycle_count % this->config->get_fixed_income_interval() != 0) {
		return;
	}

	for (auto& trader_rec : this->traders) {
		trader_rec.cash_balance += trader_rec.fixed_income;
	}
}
