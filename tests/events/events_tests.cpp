#include "events_tests.h"
#include "../cc_test.h"
#include "../../lib/external/gtest_lite.h"
#include "../../src/events/EventDispatcher.h"
#include "../../src/company/CompanyBuilder.h"
#include "../../src/company/Company.h"
#include "../../lib/memory/Rc.h"
#include "../../lib/collections/Vector.h"
#include "../../lib/rand/RandomProvider.h"
#include "../../src/config/Config.h"
#include "./events_mock.h"
#include "../company/company_mock.h"

using nhflib::RandomProvider;
using nhflib::Rc;
using event::EventDispatcher;
using event::Event;
using event::EventTarget;
using company::CompanyBuilder;
using nhflib::Vector;
using company::Company;


CC_TEST(void run_events_tests(), {
	TEST(Events, DispatcherSanity)
	{
		CompanyBuilder builder(mock_rng(), mock_config());
		auto companies = nhflib::make_rc_ctr<Vector<Company>>();
		companies->push_back(builder.build_random(0));

		auto dispatcher = mock_event_dispatcher();
		EXPECT_NO_THROW(auto
		events = dispatcher->dispatch_events(EventDispatchingContext{
				0,
				companies
		}););
	}
	END

	EventTester et;
	et.run_classed_event_tests();
})

CC_TEST(void EventTester::run_classed_event_tests(), {

	TEST(Events, GenerateEvent_Global)
	{
		auto dispatcher = mock_event_dispatcher();
		auto companies = nhflib::make_rc_ctr<Vector<Company>>();
		auto events_out = nhflib::make_rc_ctr<Vector<Event>>();
		companies->push_back(mock_company_one());

		EventDispatchingContext context;
		context.at_cycle = 0;
		context.companies = companies;

		while (events_out->size() == 0) {
			dispatcher->generate_events_for_target(context, EventTarget::Global, events_out);
		}

		EXPECT_TRUE(events_out->size() != 0);
		auto generated_event = events_out->at(0);
		EXPECT_TRUE(generated_event->target == EventTarget::Global);
		EXPECT_TRUE(!generated_event->company_target.is_some());
		EXPECT_TRUE(!generated_event->sector_target.is_some());
	}
	END
})
