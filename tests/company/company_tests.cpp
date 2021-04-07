#include "company_tests.h"

#ifdef ETEST
#include "iostream"
#include "../../lib/external/gtest_lite.h"
#include "../../src/company/CompanyBuilder.h"
#include "../../lib/rand/RandomProvider.h"
#include "../../lib/option/Option.h"

using nhflib::RandomProvider;
using nhflib::Option;
using company::CompanyBuilder;
using company::Company;

void run_company_tests() {
	TEST(Company, BuilderWorks)
	{
		Option<usize> seed(10);
		RandomProvider rng_base(seed);
		std::shared_ptr<RandomProvider> rng = std::make_shared<RandomProvider>(rng_base);

		CompanyBuilder builder(rng);

		Company cmp = builder.build_random();
		EXPECT_TRUE(cmp.get_name().len() > 0);
		EXPECT_TRUE(cmp.get_sector() > 0);
	}
	END
}

#else

void run_company_tests() {}

#endif