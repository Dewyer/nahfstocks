#pragma once

#include "../../../lib/types.h"
#include "../../../lib/memory/Rc.h"
#include "../../cli/CliHelper.h"
#include "TraderRecordInExchange.h"
#include "MarketContext.h"
#include "Order.h"

using nhflib::Rc;
using exchange::TraderRecordInExchange;
using cli::CliHelper;

namespace exchange {

	class Exchange;

	class ExchangeApi {
	private:
		exchange::Exchange *exchange;
		Rc<TraderRecordInExchange> trader;
		Rc<MarketContext> context;
		Rc<CliHelper> cli;

	public:
		ExchangeApi(exchange::Exchange *_exchange, const nhflib::Rc<MarketContext> &_context,
					const nhflib::Rc<exchange::TraderRecordInExchange> &_trader, const Rc<CliHelper> &_cli) :
				exchange(_exchange),
				trader(_trader),
				context(_context),
				cli(_cli) {}

		Rc<CliHelper> get_cli() {
			return this->cli;
		}

		const MarketContext &get_market_context() const noexcept {
			return *this->context;
		}

		usize get_trader_balance() const noexcept {
			return this->trader->total_balance;
		}

		usize get_trader_id() const noexcept {
			return this->trader->trader_id;
		}

		usize get_trader_income() const noexcept {
			return this->trader->fixed_income;
		}

		exchange::Order open_order(exchange::OrderCreationPayload order);

		Vector<exchange::Order> get_orders();

		Vector<TraderStock> get_owned_stocks();

		void cancel_order(usize order_id);
	};
}
