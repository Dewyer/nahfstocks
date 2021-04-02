#pragma once

#include "../../trader/ITrader.h"
#include "../../../lib/types.h"

using trader::ITrader;


namespace exchange {
    class TraderRecordInExchange {
    public:
        ITrader trader;

        usize cash_balance;

        TraderRecordInExchange(ITrader trader, usize starting_cash);
    };
}
