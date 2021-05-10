#pragma once
#include "iostream"
#include "../../lib/string/String.h"

using nhflib::String;

namespace utils {
	/// Formats a monetari value to be displayed on the console
	String format_money(usize money);
}