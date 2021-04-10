#include "TraderAgent.h"

const nhflib::String &trader::TraderAgent::get_name() const noexcept {
	return this->name;
}

void trader::TraderAgent::print_debug(std::ostream &os) const noexcept {
	os << "T[" << this->get_name() << "]" <<std::endl;
}
