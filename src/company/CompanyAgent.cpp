#include "CompanyAgent.h"
#include "../exchange/exchange_api/ExchangeApi.h"
#include "../exchange/exchange_api/Order.h"

void company::CompanyAgent::on_cycle(exchange::ExchangeApi &api) {
	api.get_logger_stream() << "CA:" << this->get_name() << "[" << api.get_trader_id() << "]" << std::endl;

	auto orders = api.get_orders();
	if (orders.size())
		return;

	auto stocks = api.get_owned_stocks();
	if (!stocks.size())
		return;

	auto my_company_stock = stocks.at(0);

	api.open_order(exchange::OrderCreationPayload{
			exchange::OrderType::Sell,
			my_company_stock->company_id,
			my_company_stock->amount,
			this->per_share_starter,
			Option<usize>()
	});

	api.get_logger_stream() << my_company_stock->amount << " shares for comp:" << my_company_stock->company_id << ", "
							<< (my_company_stock->amount * this->per_share_starter) << "$ worth, listed." << std::endl;
}

usize company::CompanyAgent::get_company() const noexcept {
	return this->company_id;
}
