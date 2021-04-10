#pragma once

#include "../../trader/Trader.h"
#include "../../../lib/string/String.h"
#include "../../../lib/collections/Vector.h"
#include "../../../lib/memory/Rc.h"
#include "../../../lib/types.h"

using nhflib::String;
using nhflib::Vector;
using nhflib::Rc;
using trader::Trader;

namespace exchange {

	struct TraderStock {
		usize company_id;
		usize count;
	};

    class TraderRecordInExchange {
    public:
        Rc<Trader> trader;
        usize cash_balance;
		Vector<TraderStock> stocks;

        TraderRecordInExchange(const Rc<Trader>& trader, usize starting_cash) {
			this->trader = trader;
			this->cash_balance = starting_cash;
		}
	};
}
