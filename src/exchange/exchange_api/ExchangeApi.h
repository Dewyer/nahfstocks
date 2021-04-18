#pragma once

#include "../../../lib/types.h"
#include "../../../lib/memory/Rc.h"
#include "TraderRecordInExchange.h"
#include "MarketContext.h"
#include "Order.h"

namespace exchange {

	class Exchange;

	class ExchangeApi {
	private:
		exchange::Exchange *exchange;
		nhflib::Rc<exchange::TraderRecordInExchange> trader;
		nhflib::Rc<MarketContext> context;
		std::ostream *logger_stream;


	public:
		ExchangeApi(exchange::Exchange *_exchange, const nhflib::Rc<MarketContext> &_context,
					const nhflib::Rc<exchange::TraderRecordInExchange> &_trader, std::ostream *_logger_stream) :
				exchange(_exchange),
				trader(_trader),
				context(_context),
				logger_stream(_logger_stream) {}

		std::ostream &get_logger_stream() const noexcept {
			return *this->logger_stream;
		}

		const MarketContext &get_market_context() const noexcept {
			return *this->context;
		}

		usize get_trader_balance() const noexcept {
			return this->trader->cash_balance;
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
