#pragma once

#include "../../lib/memory/Rc.h"
#include "../../src/company/Company.h"

using nhflib::Rc;
using company::Company;

Rc<Company> mock_company_one() {
	Company cmp(0, "Test One", "T1", 0.5, 0.5, 0.1, 10, 40000);
	return nhflib::make_rc(cmp);
}
