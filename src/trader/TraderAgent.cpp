#include "TraderAgent.h"
#include "../exchange/exchange_api/ExchangeApi.h"

const nhflib::String &trader::TraderAgent::get_name() const noexcept {
	return this->name;
}

void trader::TraderAgent::on_cycle(exchange::ExchangeApi &api) {
	// TODO: Implement
	if (0 == 1) {
		api.get_orders();
	}
}

void trader::TraderAgent::print_to(Rc<CliHelper> cli) const noexcept {
	cli->os() << "T[" << this->get_name() << "]";
	cli->print_ln();
}
