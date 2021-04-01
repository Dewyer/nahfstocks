#pragma once

#include "../../lib/types.h"
#include <string>

namespace company {
	class ICompany {

	public:
		virtual const std::string& get_symbol() const noexcept = 0;

		virtual const std::string& get_name() const noexcept = 0;

		virtual double get_sector() const noexcept = 0;
	};
}