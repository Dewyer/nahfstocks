#pragma once

#include "../../lib/rand/RandomProvider.h"
#include "../../lib/memory/Rc.h"
#include "../../lib/string/String.h"
#include "./Company.h"
#include <memory>
#include <utility>

using nhflib::RandomProvider;
using nhflib::String;

namespace company {

	struct CompanyName {
		String name;
		String symbol;
	};

	class CompanyBuilder {
		nhflib::Rc<RandomProvider> rng;

	private:
		CompanyName get_random_name();

	public:
		explicit CompanyBuilder(const nhflib::Rc<RandomProvider> &_rng) {
			this->rng = _rng;
		}

		Company build_random(usize id);
	};

}