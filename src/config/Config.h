#pragma once

#include "../../lib/types.h"
#include "../../lib/option/Option.h"

using nhflib::Option;

namespace config {
	class Config {
	public:

		usize get_company_count() const noexcept {
			return 40;
		}

		usize get_trader_count() const noexcept {
			return 40;
		}

		usize get_fixed_income_interval() const noexcept {
			return 24*30;
		}

		usize get_median_starting_cash() const noexcept {
			return 10000;
		}

		void read_from_cin();
	};
}