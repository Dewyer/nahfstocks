#include "./Order.h"
#include "../../exchange/exchange_api/TraderRecordInExchange.h"
// ^^^ This is weird

namespace exchange {
	String order_type_to_string(const OrderType &type) {
		switch (type) {
			case OrderType::Sell:
				return "Sell";
			case OrderType::Buy:
				return "Buy";
			default:
				return "Other";
		}
	}
}