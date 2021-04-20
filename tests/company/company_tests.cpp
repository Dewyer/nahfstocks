#include "company_tests.h"
#include "iostream"
#include "../../lib/external/gtest_lite.h"
#include "../../src/company/CompanyBuilder.h"
#include "../../lib/rand/RandomProvider.h"
#include "../../lib/memory/Rc.h"
#include "../../lib/option/Option.h"
#include "../cc_test.h"

using nhflib::RandomProvider;
using nhflib::Option;
using company::CompanyBuilder;
using company::Company;

CC_TEST(void run_company_tests(), {
	TEST(Company, Builder)
	{
		Option<usize> seed(10);
		RandomProvider rng_base(seed);
		auto cnf = nhflib::make_rc_ctr<config::Config>();

		nhflib::Rc<RandomProvider> rng = nhflib::Rc<RandomProvider>::make_rc(rng_base);

		CompanyBuilder builder(rng, cnf);

		auto cmp = builder.build_random(0);
		EXPECT_TRUE(cmp->get_name().len() > 0);
		EXPECT_TRUE(cmp->get_sector() > 0);
	}
	END
})
