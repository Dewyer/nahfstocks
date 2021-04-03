#pragma once

#include "../../lib/types.h"
#include "../../lib/string/String.h"
using nhflib::String;

namespace company {
    class ICompany {
    public:
        virtual ~ICompany() = 0;

        virtual const String &get_symbol() const noexcept = 0;

        virtual const String &get_name() const noexcept = 0;

        virtual double get_sector() const noexcept = 0;
    };
}