#pragma once

#include "../../src/exchange/ExchangeBuilder.h"
#include "../../lib/memory/Rc.h"
#include "../lib/lib_mocks.h"
#include "../config/config_mock.h"

using nhflib::Rc;
using exchange::ExchangeBuilder;

Rc<ExchangeBuilder> mock_exchange_builder();