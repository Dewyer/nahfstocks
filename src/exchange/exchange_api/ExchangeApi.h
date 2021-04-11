#pragma once

#include "../../../lib/types.h"
#include "../../../lib/memory/Rc.h"
#include "TraderRecordInExchange.h"

namespace exchange {
	class ExchangeApi {
	private:
		nhflib::Rc<exchange::TraderRecordInExchange> trader;

	public:
		explicit ExchangeApi(nhflib::Rc<exchange::TraderRecordInExchange> _trader) : trader(_trader) {}

		usize get_trader_balance() const noexcept {
			return this->trader->cash_balance;
		}

		usize get_trader_id() const noexcept {
			return this->trader->trader_id;
		}

		usize get_trader_income() const noexcept {
			return this->trader->fixed_income;
		}
	};
}
