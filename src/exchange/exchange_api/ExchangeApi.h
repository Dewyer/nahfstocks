#pragma once

#include "IExchangeApi.h"
#include "../../../lib/types.h"

namespace exchange {
	class ExchangeApi: public IExchangeApi {
	private:
		usize trader_balance;

	public:
		ExchangeApi();

		usize get_trader_balance() const noexcept override;
	};
}
