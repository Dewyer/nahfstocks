//
// Created by Barna on 2021. 04. 10..
//

#include "TraderAgentBuilder.h"

nhflib::Rc<trader::TraderAgent> trader::TraderAgentBuilder::build_random() {
	TraderAgent agent("Trader joe");
	return nhflib::make_rc(agent);
}
