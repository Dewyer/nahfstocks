#pragma once

#include "../../lib/types.h"
#include "../../lib/option/Option.h"

using nhflib::Option;

namespace exchange {
	class ExchangeConfig {
	public:

		usize get_company_count() const noexcept {
			return 40;
		}

		usize get_trader_count() const noexcept {
			return 40;
		}


		usize get_median_starting_cash() const noexcept {
			return 2000;
		}
	};
}