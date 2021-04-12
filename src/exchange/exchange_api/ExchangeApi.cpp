
#include "ExchangeApi.h"
#include "../Exchange.h"

exchange::Order exchange::ExchangeApi::open_order(exchange::OrderCreationPayload order) {
	return this->exchange->open_order(this->trader, order);
}

void exchange::ExchangeApi::cancel_order(usize order_id) {
	this->exchange->cancel_order(this->trader, order_id);
}
