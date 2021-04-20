#include "exchange_mock.h"

Rc<ExchangeBuilder> mock_exchange_builder() {
	ExchangeBuilder builder(mock_rng(), mock_config());
	return nhflib::make_rc(builder);
}
