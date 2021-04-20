#pragma once

#include "../../src/events/EventDispatcher.h"
#include "../../lib/memory/Rc.h"
#include "../lib/lib_mocks.h"
#include "../config/config_mock.h"

using nhflib::Rc;
using event::EventDispatcher;


Rc<event::EventDispatcher> mock_event_dispatcher() {
	auto rng_rc = mock_rng();
	auto config = mock_config();

	event::EventDispatcher dispatcher(rng_rc, config);
	return nhflib::make_rc(dispatcher);
}
