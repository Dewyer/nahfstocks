#pragma once

#include <cstdlib>
#include "../types.h"

namespace nhflib {
	class RandomProvider {
	private:
		void initialize(u32* seed);
	public:
		explicit RandomProvider(u32 seed) {
			this->initialize(&seed);
		}

		explicit RandomProvider() {
			this->initialize(nullptr);
		}
	};
}
