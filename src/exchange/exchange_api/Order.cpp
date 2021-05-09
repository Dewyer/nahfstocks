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

	Order::Order(usize _id, usize _trader_id,
				 const OrderCreationPayload &payload): OrderCreationPayload(payload) {
		this->id = _id;
		this->trader_id = _trader_id;
	}
}