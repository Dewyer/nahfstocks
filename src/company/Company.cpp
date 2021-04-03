#include "Company.h"
#include "../../lib/string/String.h"
using nhflib::String;

const String &company::Company::get_name() const noexcept {
    return this->name;
}

double company::Company::get_sector() const noexcept {
    return this->sector;
}

const String &company::Company::get_symbol() const noexcept {
    return this->name;
}

company::Company::Company(const String& _name, const String& _sym, f64 _financial_standing, f64 _sector, f64 _leadership_bias,
						  usize _earnings_offset) {
	this->name = _name;
	this->symbol = _sym;
	this->financial_standing = _financial_standing;
	this->sector = _sector;
	this->leadership_bias = _leadership_bias;
	this->earnings_offset = _earnings_offset;
}
