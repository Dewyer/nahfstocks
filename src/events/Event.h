#pragma once

#include "../../lib/option/Option.h"
#include "../../lib/types.h"

using nhflib::Option;

namespace event {
	enum EventTarget {
		Global,
		Sector,
		Company
	};

	class Event {
	public:
		EventTarget target;
		Option<usize> company_target;
		Option<f64> sector_target;

		f64 weight;
		f64 nonce;
		f64 sentiment;
	};
}