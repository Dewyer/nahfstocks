#pragma once
#include "../../lib/option/Option.h"
#include "../../lib/types.h"
#include "../../lib/string/String.h"

using nhflib::Option;
using nhflib::String;

namespace event {
	enum EventTarget {
		Global,
		Sector,
		Company
	};

	String event_target_to_string(EventTarget target);

	class Event {
	public:
		usize id;
		usize created_at;
		EventTarget target;
		Option<usize> company_target;
		Option<f64> sector_target;

		f64 weight;
		f64 nonce;
		f64 sentiment;

		Event() {}

		Event(const Event& rhs) {
			this->created_at = rhs.created_at;
			this->target = rhs.target;
			this->company_target = rhs.company_target ? Option<usize>(rhs.company_target) : Option<usize>();
			this->sector_target = rhs.sector_target ? Option<f64>(rhs.sector_target) : Option<f64>();
			this->weight = rhs.weight;
			this->nonce = rhs.nonce;
			this->sentiment = rhs.sentiment;
		}
	};
}