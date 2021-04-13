#pragma once
#include "../../lib/types.h"
#include "../../lib/collections/Vector.h"
#include "../../lib/memory/Rc.h"
#include "../company/Company.h"


class EventDispatchingContext {
public:
	usize at_cycle;
	nhflib::Rc<nhflib::Vector<company::Company>> companies;
};