#pragma once

#include "../../trader/TraderAgent.h"
#include "../../../lib/string/String.h"
#include "../../../lib/collections/Vector.h"
#include "../../../lib/memory/Rc.h"
#include "../../../lib/types.h"
#include "./Order.h"

using nhflib::String;
using nhflib::Vector;
using nhflib::Rc;
using trader::TraderAgent;

namespace exchange {

	struct TraderStock {
		usize company_id;
		usize amount;
	};

	class TraderRecordInExchange {
	public:
		usize trader_id;
		Rc<TraderAgent> trader;
		usize cash_balance;
		usize fixed_income;
		Vector<TraderStock> stocks;

		usize next_activation;

		nhflib::Vector<nhflib::Rc<exchange::Order>> open_orders;

		TraderRecordInExchange(usize _trader_id, const Rc<TraderAgent> &trader, usize starting_cash, usize _fixed_income) {
			this->trader_id = _trader_id;
			this->trader = trader;
			this->cash_balance = starting_cash;
			this->fixed_income = _fixed_income;
		}

		void print_debug(std::ostream &os) const noexcept {
			this->trader->print_debug(os);
			os << "| Bal: " << this->cash_balance << ", Inc: " << this->fixed_income << std::endl;
		}
	};
}
