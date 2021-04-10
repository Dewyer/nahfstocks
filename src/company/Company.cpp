#include "Company.h"
#include "../../lib/string/String.h"
#include "../../lib/types.h"

using nhflib::String;

const String &company::Company::get_name() const noexcept {
	return this->name;
}

f64 company::Company::get_sector() const noexcept {
	return this->sector;
}

const String &company::Company::get_symbol() const noexcept {
	return this->symbol;
}

company::Company::Company(usize id, const String &_name, const String &_sym, f64 _financial_standing, f64 _sector,
						  f64 _leadership_bias,
						  usize _earnings_offset) {
	this->id = id;
	this->name = _name;
	this->symbol = _sym;
	this->financial_standing = _financial_standing;
	this->sector = _sector;
	this->leadership_bias = _leadership_bias;
	this->earnings_offset = _earnings_offset;
}

void company::Company::print_debug(std::ostream &os) const noexcept {
	os << "=[" << this->id << "]= " << this->get_name().c_str() << " - [" << this->get_symbol().c_str() << "]"
	   << std::endl;
	os << "Sector: " << this->get_sector() << ", Financials: " << this->financial_standing << ", Leadership: "
	   << this->leadership_bias << std::endl;
}

usize company::Company::get_id() const noexcept {
	return this->id;
}
