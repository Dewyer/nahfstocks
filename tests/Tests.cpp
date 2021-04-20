#include "../lib/external/gtest_lite.h"
#include "./lib/lib_tests.h"
#include "./company/company_tests.h"
#include "./events/events_tests.h"
#include "./trader/trader_tests.h"
#include "./exchange/exchange_tests.h"

#include "cc_test.h"

#include "Tests.h"

CC_TEST(void Tests::sanity_test(), {
	TEST(SanityTest, SanityTest)
	{
		EXPECT_EQ(10, 10);
	}
	END
})


CC_TEST(void Tests::run_all(), {
	Tests::sanity_test();
	run_lib_tests();
	run_company_tests();
	run_events_tests();
	run_trader_tests();

	ExchangeTester et;
	et.run_exchange_tests();
})
