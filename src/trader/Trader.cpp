#include "Trader.h"

usize trader::Trader::get_id() const noexcept {
	return this->id;
}

const nhflib::String &trader::Trader::get_name() const noexcept {
	return this->name;
}
