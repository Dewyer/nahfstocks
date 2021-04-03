#pragma once

#include "ICompany.h"
#include "../../lib/string/String.h"

using nhflib::String;
using company::ICompany;

namespace company {
    class Company : public ICompany {
    private:
        std::string name;
        // double financial_standing;
        double sector;
        // double leadership_bias;
        // usize earnings_offset;
    public:
        const String &get_symbol() const noexcept override;

        const String &get_name() const noexcept override;

        double get_sector() const noexcept override;
    };
}
