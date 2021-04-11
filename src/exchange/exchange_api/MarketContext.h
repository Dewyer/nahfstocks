#pragma once
#include "../../../lib/memory/Rc.h"
#include "../../../lib/collections/Vector.h"
using nhflib::Rc;
using nhflib::Vector;

namespace exchange {
	class MarketContext {
	public:
		Rc<Vector<Rc<Company>>> companies;
	};
}