#pragma once
#include "../../lib/rand/RandomProvider.h"
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
		std::shared_ptr<RandomProvider> rng;

	private:
		CompanyName get_random_name();

	public:
		explicit CompanyBuilder(std::shared_ptr<RandomProvider> _rng) {
			this->rng = std::move(_rng);
		}

		Company build_random();
	};

}