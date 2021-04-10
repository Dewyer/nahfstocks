#pragma once
#include "../../lib/string/String.h"

namespace trader {
    class ITrader {
    private:

	public:
		virtual usize get_id() const noexcept = 0;

		virtual const nhflib::String &get_name() const noexcept = 0;
    };
}