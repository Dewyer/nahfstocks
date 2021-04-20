#pragma once

#include "../../lib/types.h"
#include "../../lib/option/Option.h"

using nhflib::Option;

namespace config {
	class Config {
	public:

		virtual usize get_company_count() const noexcept {
			return 40;
		}

		virtual usize get_trader_count() const noexcept {
			return 40;
		}

		virtual usize get_fixed_income_interval() const noexcept {
			return 24 * 30;
		}

		virtual usize get_median_starting_cash() const noexcept {
			return 10000;
		}

		virtual usize get_mean_company_outstanding_shares() const noexcept {
			return 1200000;
		}

		virtual f64 get_global_event_chance() const noexcept {
			return 0.01;
		}

		virtual f64 get_sector_event_chance() const noexcept {
			return 0.01;
		}

		virtual f64 get_company_event_chance() const noexcept {
			return 0.01;
		}

		virtual bool should_log() const noexcept {
			return true;
		}

		virtual ~Config() {}

		virtual void read_from_cin() {}
	};
}