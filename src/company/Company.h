#pragma once

#include "ICompany.h"
using company::ICompany;

namespace company {
	class Company : public ICompany {
	private:
		std::string name;
		double financial_standing;
		double sector;
		double leadership_bias;
		usize earnings_offset;
	public:
		const std::string& get_name() const noexcept override;

		double get_sector() const noexcept override;
	};
}
