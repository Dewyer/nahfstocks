#pragma once

#include "../../lib/collections/Vector.h"
#include "../../lib/memory/Rc.h"
#include "Event.h"
#include "EventDispatchingContext.h"

namespace event {
	class EventDispatcher {
		nhflib::Rc<nhflib::RandomProvider> rng;
	public:
		explicit EventDispatcher(const nhflib::Rc<nhflib::RandomProvider> &_rng) : rng(_rng) {}

		nhflib::Vector<Event> dispatch_events(const EventDispatchingContext &context);
	};
}
