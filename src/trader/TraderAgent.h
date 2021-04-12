#pragma once

#include "../../lib/string/String.h"

namespace exchange {
	class ExchangeApi;
}

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

