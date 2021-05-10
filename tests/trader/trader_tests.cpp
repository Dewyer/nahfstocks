#include "trader_tests.h"
#include "../cc_test.h"
#include "../../lib/memory/Rc.h"
#include "../../src/trader/TraderAgentBuilder.h"
#include "../lib/lib_mocks.h"
#include "../../lib/external/gtest_lite.h"
#include "../config/config_mock.h"


using trader::TraderAgentBuilder;
using trader::TraderAgent;

CC_TEST(void run_trader_tests(), {
	TEST(TraderAgent, Builder)
	{
		TraderAgentBuilder agent_builder(mock_rng(), mock_config());

		auto trader = agent_builder.build_random();
		EXPECT_TRUE(trader->get_name().len() > 0);
	}
	END
})
