#include "exchange_mock.h"
#include "../cli/cli_mock.h"

Rc<ExchangeBuilder> mock_exchange_builder() {
	ExchangeBuilder builder(mock_rng(), mock_config(), mock_cli());
	return nhflib::make_rc(builder);
}
