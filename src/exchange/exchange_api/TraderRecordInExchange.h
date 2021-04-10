#pragma once

#include "../../trader/TraderAgent.h"
#include "../../../lib/string/String.h"
#include "../../../lib/collections/Vector.h"
#include "../../../lib/memory/Rc.h"
#include "../../../lib/types.h"

using nhflib::String;
using nhflib::Vector;
using nhflib::Rc;
using trader::TraderAgent;

namespace exchange {

	struct TraderStock {
		usize company_id;
		usize count;
	};

	class TraderRecordInExchange {
	public:
		usize trader_id;
		Rc<TraderAgent> trader;
		usize cash_balance;
		Vector<TraderStock> stocks;

		TraderRecordInExchange(usize _trader_id, const Rc<TraderAgent> &trader, usize starting_cash) {
			this->trader_id = _trader_id;
			this->trader = trader;
			this->cash_balance = starting_cash;
		}
	};
}
