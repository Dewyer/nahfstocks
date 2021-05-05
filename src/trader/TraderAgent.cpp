#include "TraderAgent.h"
#include "../exchange/exchange_api/ExchangeApi.h"

const nhflib::String &trader::TraderAgent::get_name() const noexcept {
	return this->name;
}

void trader::TraderAgent::on_cycle(exchange::ExchangeApi &api) {
	auto log_stream = api.get_logger_stream();
	if (!log_stream) {
		return;
	}

	*log_stream.unwrap() << "Trader activated: " << api.get_trader_id() << std::endl;
}

void trader::TraderAgent::print_to(Rc<CliHelper> cli) const noexcept {
	cli->os() << "T[" << this->get_name() << "]";
	cli->print_ln();

}
