#pragma once

#include "../../lib/string/String.h"

namespace trader {
	class TraderAgent {
		nhflib::String name;
	public:

		explicit TraderAgent(const nhflib::String &name) {
			this->name = name;
		}

		void print_debug(std::ostream &os) const noexcept;

		const nhflib::String &get_name() const noexcept;
	};
}

