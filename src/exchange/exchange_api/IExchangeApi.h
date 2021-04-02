#pragma once

#include "../../../lib/types.h"

class IExchangeApi {
public:
    virtual usize get_trader_balance() const noexcept = 0;
};