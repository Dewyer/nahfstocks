#include "./cli_mock.h"

Rc<CliHelper> mock_cli() {
	return nhflib::make_rc(CliHelper(nullptr, &std::cin));
}
