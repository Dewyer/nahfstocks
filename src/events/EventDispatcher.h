#pragma once

#include "../../lib/rand/RandomProvider.h"
#include "../../lib/collections/Vector.h"
#include "../../lib/memory/Rc.h"
#include "Event.h"
#include "EventDispatchingContext.h"
#include "../config/Config.h"
#include "../../tests/events/events_tests.h"

using nhflib::Vector;
using nhflib::Rc;
using nhflib::RandomProvider;
using config::Config;

namespace event {
	/// Dispatches events on every cycle, managed by an exchange instance
	class EventDispatcher {
	private:
		usize next_event_id;

		Rc<RandomProvider> rng;
		Rc<Config> config;

		static usize event_target_type_count;
		static EventTarget event_target_types[3];

		f64 get_rollover_chance_for_target(EventTarget target) const;

		void generate_events_for_target(const EventDispatchingContext &context, EventTarget target,
										Rc<Vector<Event>> events_out);

		void
		generate_target_specific_event_parts(const EventDispatchingContext &context, Rc<Event> &ev, EventTarget target);

	public:
		explicit EventDispatcher(const Rc<RandomProvider> &_rng, const Rc<config::Config> &_config) : next_event_id(0),
																									  rng(_rng),
																									  config(_config) {}

		Rc<Vector<Event>> dispatch_events(const EventDispatchingContext &context);

		friend EventTester;
	};
}
