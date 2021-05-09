#pragma once

#include "../../lib/string/String.h"
#include "../cli/CliHelper.h"

using cli::CliHelper;

namespace exchange {
	class ExchangeApi;
}

namespace trader {
	struct TraderAgentInitPayload {
		usize agent_id;
	};

	class TraderAgent {
		nhflib::String name;
		usize id;
	public:

		explicit TraderAgent(const nhflib::String &name) {
			this->name = name;
			this->id = 0;
		}

		virtual void print_to(Rc<CliHelper> cli) const noexcept;

		virtual const nhflib::String &get_name() const noexcept;

		virtual void init(TraderAgentInitPayload payload);

		virtual void on_cycle(exchange::ExchangeApi &api);

		virtual ~TraderAgent() = default;
	};
}

