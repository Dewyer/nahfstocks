#include "TraderAgent.h"
#include "../exchange/exchange_api/ExchangeApi.h"

const nhflib::String &trader::TraderAgent::get_name() const noexcept {
	return this->name;
}

void trader::TraderAgent::on_cycle(exchange::ExchangeApi &api) {
	api.get_unseen_events();
}

void trader::TraderAgent::print_to(Rc<CliHelper> cli) const noexcept {
	cli->os() << "T[" << this->get_name() << "]";
	cli->print_ln();
}

void trader::TraderAgent::init(trader::TraderAgentInitPayload payload) {
	this->id = payload.agent_id;
}
