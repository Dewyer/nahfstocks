#include "Company.h"

const std::string& company::Company::get_name() const noexcept {
	return this->name;
}

double company::Company::get_sector() const noexcept {
	return this->sector;
}
