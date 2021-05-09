#include "EventDispatcher.h"
#include "../../lib/memory/Rc.h"

using nhflib::Rc;
using event::EventTarget;
using event::Event;
using event::EventDispatcher;

EventTarget EventDispatcher::event_target_types[3] = {EventTarget::Global, EventTarget::Company, EventTarget::Sector};
usize EventDispatcher::event_target_type_count = 3;

void EventDispatcher::generate_events_for_target(const EventDispatchingContext &context, EventTarget target,
												 Rc<Vector<Event>> events_out) {
	while (true) {
		auto generated_event = this->rng->next_bool(EventDispatcher::get_rollover_chance_for_target(target));

		if (!generated_event)
			return;
		auto ev = nhflib::make_rc_ctr<Event>();
		ev->id = this->next_event_id++;
		ev->created_at = context.at_cycle;
		ev->target = target;
		this->generate_target_specific_event_parts(context, ev, target);
		ev->nonce = this->rng->next_normal();
		ev->sentiment = this->rng->next_f64_normal(0, 1, 0.5, 0.3);

		events_out->push_back(ev);
	}
}

void event::EventDispatcher::generate_target_specific_event_parts(const EventDispatchingContext &context, Rc<Event> &ev,
																  EventTarget target) {
	switch (target) {
		case EventTarget::Global:
			ev->weight = this->rng->next_f64_normal(0, 1, 0.8, 0.5);
			return;
		case EventTarget::Sector:
			ev->weight = this->rng->next_f64_normal(0, 1, 0.5, 0.3);
			ev->sector_target = Option<f64>(this->rng->next_normal());
			return;
		case EventTarget::Company:
			ev->weight = this->rng->next_f64_normal(0, 1, 0.5, 0.25);
			ev->company_target = Option<usize>(this->rng->next_usize(0, context.companies->size() - 1));
			return;
	}
}

Rc<Vector<Event>> EventDispatcher::dispatch_events(const EventDispatchingContext &context) {
	auto events_dispatched = nhflib::make_rc_ctr<Vector<Event>>();
	for (usize ii = 0; ii < EventDispatcher::event_target_type_count; ii++) {
		this->generate_events_for_target(context, EventDispatcher::event_target_types[ii], events_dispatched);
	}

	return events_dispatched;
}

f64 EventDispatcher::get_rollover_chance_for_target(EventTarget target) const {
	switch (target) {
		case EventTarget::Global:
			return this->config->get_global_event_chance();
		case EventTarget::Sector:
			return this->config->get_sector_event_chance();
		case EventTarget::Company:
			return this->config->get_company_event_chance();
		default:
			return 0;
	}
}

