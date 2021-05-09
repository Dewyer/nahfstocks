#pragma once

#include "../../../lib/memory/Rc.h"
#include "../../../lib/collections/Vector.h"
#include "../../company/Company.h"

using nhflib::Rc;
using nhflib::Vector;
using company::Company;

namespace exchange {
	class MarketContext {
	public:
		Rc<Vector<Company>> companies;
		explicit MarketContext(const Rc<Vector<company::Company>> &cc) : companies(cc) {}
	};
}