#include "./Event.h"

String event::event_target_to_string(EventTarget target) {
	switch (target) {
		case EventTarget::Global:
			return "Global";
		case EventTarget::Sector:
			return "Sector";
		case EventTarget::Company:
			return "Company";
		default:
			return "OtherEventType";
	}
}