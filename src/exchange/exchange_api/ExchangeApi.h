#pragma once

#include "../../../lib/types.h"
#include "../../../lib/memory/Rc.h"
#include "TraderRecordInExchange.h"
#include "MarketContext.h"
#include "Order.h"

namespace exchange {
	class ExchangeApi {
	private:
		nhflib::Rc<exchange::TraderRecordInExchange> trader;
		MarketContext context;

	public:
		explicit ExchangeApi(MarketContext _context, const nhflib::Rc<exchange::TraderRecordInExchange>& _trader) :
			trader(_trader),
			context(_context)
		{}

		const MarketContext& get_market_context() const noexcept {
			return this->context;
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

		void open_order(exchange::Order order);
	};
}
