#pragma once
#include "../../trader/ITrader.h"
using trader::ITrader;


namespace exchange {
	class TraderRecordInExchange {
	public:
		ITrader trader;

		double cash_balance;
	};
}
