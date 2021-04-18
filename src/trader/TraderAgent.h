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

		virtual void print_debug(std::ostream &os) const noexcept;

		virtual const nhflib::String &get_name() const noexcept;

		virtual void on_cycle(exchange::ExchangeApi &api);

		virtual ~TraderAgent() = default;
	};
}

