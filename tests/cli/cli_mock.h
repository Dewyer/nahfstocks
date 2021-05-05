#pragma once
#include "../../src/cli/CliHelper.h"
#include "../../lib/memory/Rc.h"

using nhflib::Rc;
using cli::CliHelper;

Rc<CliHelper> mock_cli() {
	return nhflib::make_rc(CliHelper(&std::cout, &std::cin));
}
