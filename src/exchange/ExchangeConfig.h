#pragma once

#include "../../lib/types.h"
#include "../../lib/option/Option.h"

using nhflib::Option;

namespace exchange {
    class ExchangeConfig {
    public:
        Option<usize> starting_cash;
    };
}