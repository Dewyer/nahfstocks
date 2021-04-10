#pragma once
#include "../../lib/string/String.h"

namespace trader {
	class Trader {
		usize id;
		nhflib::String name;
	public:
		usize get_id() const noexcept;

		const nhflib::String &get_name() const noexcept;
	};
}

