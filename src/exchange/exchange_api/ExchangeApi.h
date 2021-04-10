#pragma once
#include "../../../lib/types.h"

namespace exchange {
    class ExchangeApi {
    private:
        usize trader_balance;

    public:
        ExchangeApi();

        usize get_trader_balance() const noexcept;
    };
}
