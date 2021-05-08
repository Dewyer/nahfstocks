#pragma once

#include <sstream>
#include "../../lib/string/String.h"

using nhflib::String;

namespace utils {
	template<typename T>
	static String to_string(T arg) {
		std::ostringstream str_stream;
		str_stream << arg;
		return String(str_stream.str().c_str());
	}
}

