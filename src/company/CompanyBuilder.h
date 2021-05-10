#pragma once
#include <memory>
#include <utility>
#include "../../lib/prelude.h"
#include "../../lib/rand/RandomProvider.h"
#include "../../lib/memory/Rc.h"
#include "../../lib/string/String.h"
#include "./Company.h"


using nhflib::RandomProvider;
using nhflib::String;
using nhflib::Rc;
using config::Config;

namespace company {

	struct CompanyName {
		String name;
		String symbol;
	};

	/// Builder for company agents
	class CompanyBuilder {
		Rc<RandomProvider> rng;
		Rc<config::Config> config;

	private:
		CompanyName get_random_name();

	public:
		explicit CompanyBuilder(const nhflib::Rc<RandomProvider> &_rng, const Rc<config::Config> &_config) {
			this->rng = _rng;
			this->config = _config;
		}

		nhflib::Rc<Company> build_random(usize id);
	};

}