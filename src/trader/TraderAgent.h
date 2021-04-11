#pragma once

#include "../../lib/string/String.h"
#include "../exchange/exchange_api/ExchangeApi.h"

namespace trader {
	class TraderAgent {
		nhflib::String name;
	public:

		explicit TraderAgent(const nhflib::String &name) {
			this->name = name;
		}

		void print_debug(std::ostream &os) const noexcept;

		const nhflib::String &get_name() const noexcept;

		void on_cycle(const exchange::ExchangeApi& api);
	};
}

