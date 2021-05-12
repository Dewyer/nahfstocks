#pragma once

#include "../../lib/collections/Vector.h"
#include "../../lib/memory/Rc.h"
#include "../company/Company.h"

namespace company {
	class Company;

	class CompanyAgent;
}

using company::Company;
using nhflib::Rc;
using exchange::TraderRecordInExchange;

/// Represents statistics at a certain cycle for an exchange
class ExchangeStats {
	usize total_money;
	Rc<Company> biggest_company;
	Rc<TraderRecordInExchange> richest_trader;
	usize at_cycles;

public:
	const usize &get_total_money() const {
		return this->total_money;
	}


	const usize &get_at_cycles() const {
		return this->at_cycles;
	}

	const Rc<Company> &get_biggest_company() const {
		return this->biggest_company;
	}

	Rc<TraderRecordInExchange> get_richest_trader() {
		return this->richest_trader;
	}

	ExchangeStats(usize _total_money, const Rc<Company> &cmp, const Rc<TraderRecordInExchange> &trader,
				  usize _at_cycles)
			: total_money(_total_money),
			  biggest_company(cmp),
			  richest_trader(trader),
			  at_cycles(_at_cycles) {}
};

