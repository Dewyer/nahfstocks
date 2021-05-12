#pragma once

#include "../prelude.h"
#include "../types.h"
#include "../option/Option.h"

namespace nhflib {
	/// Random number generator, for 64 bit floats and unsigned ints, can produce numbers with normal and even distribution
	class RandomProvider {
		std::mt19937 engine;
	public:
		explicit RandomProvider(Option<usize> seed);

		void seed(Option<usize> seed);

		usize next_usize(usize min, usize max);

		f64 next_f64(f64 min, f64 max);

		f64 next_f64_normal(f64 min, f64 max, f64 mean, f64 devi);

		usize next_usize_normal(usize min, usize max, f64 mean, f64 devi);

		f64 next_normal();

		bool next_bool(f64 chance_of_being_true);
	};
}
