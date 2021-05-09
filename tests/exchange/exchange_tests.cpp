#include "exchange_tests.h"
#include "../cc_test.h"
#include "../cli/cli_mock.h"
#include "./exchange_mock.h"
#include "../../src/exchange/Exchange.h"
#include "../../src/exchange/exchange_api/ExchangeApi.h"
#include "../../lib/collections/Vector.h"
#include "../../src/trader/TraderAgent.h"
#include "../../lib/memory/Rc.h"
#include "../../lib/external/gtest_lite.h"

using nhflib::Rc;
using nhflib::Vector;
using trader::TraderAgent;
using exchange::Exchange;
using exchange::ExchangeApi;

class MockAgentOne : public TraderAgent {
public:
	bool all_assertions_correct;

	explicit MockAgentOne(const String &_name) : TraderAgent(_name) {
		this->all_assertions_correct = false;
	}

	void on_cycle(exchange::ExchangeApi &api) override {
		auto context = api.get_market_context();
		auto cmp_one = context.companies->at(0);

		if (api.get_trader_balance() < 1)
			return;

		auto created_order = api.open_order(exchange::OrderCreationPayload{
				exchange::OrderType::Buy,
				cmp_one->get_id(),
				1,
				api.get_trader_balance() - 1,
				Option<usize>()
		});

		api.cancel_order(created_order.id);

		all_assertions_correct = true;
	}
};

CC_TEST(void ExchangeTester::run_exchange_tests(), {
	TEST(Exchange, BuilderSanity)
	{
		auto exchange_builder = mock_exchange_builder();
		auto exchange = exchange_builder->build_random();

		EXPECT_TRUE(exchange->companies->size() > 0);
		EXPECT_TRUE(exchange->traders->size() > 0);
	}
	END

	TEST(Exchange, SanityRun) {
		auto exchange_builder = mock_exchange_builder();
		auto exchange = exchange_builder->build_random();

		EXPECT_NO_THROW(
		for (int ii = 0; ii < 100; ++ii) {
			exchange->cycle();
		}
		);
	}
	END

	TEST(Exchange, OpenOrder) {
		auto exchange_builder = mock_exchange_builder();
		auto trader_agents = nhflib::make_rc_ctr<Vector<TraderAgent>>();
		auto companies = exchange_builder->build_companies();

		auto mock_agent = new MockAgentOne("Mock Agent1");
		auto mock_agent_rc = nhflib::make_rc(mock_agent);
		trader_agents->push_back(mock_agent_rc.base_rc<TraderAgent>());

		Exchange exchange(mock_rng(), mock_config(), companies, trader_agents,
						  exchange_builder->build_trader_agents_for_companies(companies), mock_cli());

		for (int ii = 0; ii < 100; ++ii) {
			exchange.cycle();
		}

		EXPECT_TRUE(mock_agent_rc->all_assertions_correct);
		EXPECT_TRUE(!exchange.runtime_exception_occured);
	}
	END
})
