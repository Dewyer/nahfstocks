#pragma once
#include "./ITrader.h"
#include "../../lib/string/String.h"

namespace trader {
	class Trader : ITrader {
		usize id;
		nhflib::String name;
	public:
		usize get_id() const noexcept override;

		const nhflib::String &get_name() const noexcept override;
	};
}

