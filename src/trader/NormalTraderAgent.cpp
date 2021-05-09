#include "NormalTraderAgent.h"
#include "../exchange/exchange_api/ExchangeApi.h"

void trader::NormalTraderAgent::choose_random_settings() {
	auto get_norm_normal = [this]() {
		return this->rng->next_f64_normal(0, 1, 0.5, 0.35);
	};

	this->finance_bias = get_norm_normal();
	this->leadership_bias = get_norm_normal();
	this->sector_focus = this->rng->next_normal();
	this->focus_sector_threshold = get_norm_normal();
	this->volume_sensitivity = get_norm_normal();
	this->price_sensitivity = get_norm_normal();
}

void trader::NormalTraderAgent::on_cycle(exchange::ExchangeApi &api) {
	if (0 == 1) {
		api.get_orders();
	}
}

void trader::NormalTraderAgent::init(trader::TraderAgentInitPayload payload) {
	TraderAgent::init(payload);


}
