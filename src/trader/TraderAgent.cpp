#include "TraderAgent.h"
#include "../exchange/exchange_api/ExchangeApi.h"

const nhflib::String &trader::TraderAgent::get_name() const noexcept {
	return this->name;
}

void trader::TraderAgent::print_debug(std::ostream &os) const noexcept {
	os << "T[" << this->get_name() << "]" << std::endl;
}

void trader::TraderAgent::on_cycle(exchange::ExchangeApi &api) {
	api.get_logger_stream() << "Trader activated: " << api.get_trader_id() << std::endl;
}
