
#include "TraderRecordInExchange.h"
#include "../../../lib/types.h"

exchange::TraderRecordInExchange::TraderRecordInExchange(ITrader trader, usize starting_cash) {
    this->trader = trader;
    this->cash_balance = starting_cash;
}
