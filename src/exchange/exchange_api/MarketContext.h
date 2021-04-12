#pragma once
#include "../../../lib/memory/Rc.h"
#include "../../../lib/collections/Vector.h"
#include "../../company/Company.h"

using nhflib::Rc;
using nhflib::Vector;

namespace exchange {
	class MarketContext {
	public:
		Rc<Vector<company::Company>> companies;

		MarketContext(Rc<Vector<company::Company>> cc): companies(cc) {}
	};
}