
#include "ExchangeApi.h"
#include "../Exchange.h"

exchange::Order exchange::ExchangeApi::open_order(exchange::OrderCreationPayload order) {
	return this->exchange.open_order(this->trader, order);
}

void exchange::ExchangeApi::cancel_order(usize order_id) {
	this->exchange.cancel_order(this->trader, order_id);
}

Vector<exchange::Order> exchange::ExchangeApi::get_orders() {
	return this->trader->open_orders.clone();
}

Vector<exchange::TraderStock> exchange::ExchangeApi::get_owned_stocks() {
	return this->trader->stocks.clone();
}

Vector<Event> exchange::ExchangeApi::get_unseen_events() {
	return this->trader->events_to_see;
}
