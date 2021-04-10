
#include "ExchangeApi.h"

usize exchange::ExchangeApi::get_trader_balance() const noexcept {
	return this->trader_balance;
}

exchange::ExchangeApi::ExchangeApi() {
	this->trader_balance = 0;
}
