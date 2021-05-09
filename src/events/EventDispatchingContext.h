#pragma once
#include "../../lib/types.h"
#include "../../lib/collections/Vector.h"
#include "../../lib/memory/Rc.h"

namespace company {
	class Company;
}

class EventDispatchingContext {
public:
	usize at_cycle;
	nhflib::Rc<nhflib::Vector<company::Company>> companies;
};