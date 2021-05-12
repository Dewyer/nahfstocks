#pragma once

#include "../../lib/collections/Vector.h"
#include "../../lib/string/String.h"
#include "../cli/CliHelper.h"

namespace company {
	class Company;
}

namespace exchange {
	class ExchangeApi;
}

using company::Company;
using nhflib::Vector;
using cli::CliHelper;


namespace trader {
	struct TraderAgentInitPayload {
		usize agent_id;
		const Rc<Vector<Company>> &companies;
	};

	/// The trader agent base class, any agents have to be inherited from this, no functions are required to be implemented
	class TraderAgent {
		nhflib::String name;
		usize id;
	public:

		explicit TraderAgent(const nhflib::String &name) {
			this->name = name;
			this->id = 0;
		}

		virtual bool is_retail() const {
			return false;
		}

		virtual void print_to(Rc<CliHelper> cli) const noexcept;

		virtual const nhflib::String &get_name() const noexcept;

		virtual const usize &get_id() const noexcept;

		virtual void init(TraderAgentInitPayload payload);

		virtual void on_cycle(exchange::ExchangeApi &api);

		virtual ~TraderAgent() = default;
	};
}

