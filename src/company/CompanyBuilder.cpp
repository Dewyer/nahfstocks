#include "CompanyBuilder.h"
#include "names_data.h"

company::Company company::CompanyBuilder::build_random() {
	company::CompanyName cmp_name = this->get_random_name();
	f64 financials = this->rng->next_f64_normal(0.0,1.0, 0.5, 0.2);
	f64 sector = this->rng->next_f64(0, 1);
	f64 leadership = this->rng->next_f64(0, 1);
	usize earnings = this->rng->next_usize_normal(0, 50, 25, 10);

	Company cmp(cmp_name.name, cmp_name.symbol, financials, sector, leadership, earnings);
	return cmp;
}

company::CompanyName company::CompanyBuilder::get_random_name() {
	CompanyName full_name;

	usize name_count = this->rng->next_usize_normal(1, 8, 0.5, 0.25);
	for (usize ii = 0; ii < name_count; ++ii) {
		usize name_ind = this->rng->next_usize(0, COMPANY_NAME_WORD_LIST_LENGTH);
		if (full_name.name.len() > 0) {
			full_name.name += " ";
		}

		String new_part = company_name_word_list[name_ind];
		if (new_part != "Inc" && new_part != "Ltd") {
			full_name.symbol += toupper(new_part[0]);
		}
		full_name.name += new_part;
	}
	return full_name;
}
0