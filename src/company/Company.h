#pragma once

#include "ICompany.h"
#include "../../lib/string/String.h"

using nhflib::String;
using company::ICompany;

namespace company {
    class Company : public ICompany {
    private:
		String name;
		String symbol;
		f64 financial_standing;
        f64 sector;
		f64 leadership_bias;
		usize earnings_offset;
    public:
    	Company(const String& _name, const String& _sym, f64 _financial_standing, f64 _sector, f64 _leadership_bias, usize _earnings_offset );

        const String &get_symbol() const noexcept override;

        const String &get_name() const noexcept override;

		f64 get_sector() const noexcept override;
    };
}
