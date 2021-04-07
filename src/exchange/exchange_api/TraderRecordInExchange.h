#pragma once

#include "../../trader/ITrader.h"
#include "../../../lib/string/String.h"
#include "../../../lib/collections/Vector.h"
#include "../../../lib/types.h"

using trader::ITrader;
using nhflib::String;
using nhflib::Vector;

namespace exchange {

	struct TraderStock {
		usize company_id;
		usize count;
	};

    class TraderRecordInExchange {
    public:
        ITrader trader;
        usize cash_balance;
		Vector<TraderStock> stocks;

        TraderRecordInExchange(ITrader trader, usize starting_cash);
    };
}
