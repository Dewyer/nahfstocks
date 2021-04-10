#include "ExchangeBuilder.h"
#include "../../lib/collections/Vector.h"
#include "../trader/Trader.h"
#include "../company/CompanyBuilder.h"

using nhflib::Vector;
using company::CompanyBuilder;

Exchange exchange::ExchangeBuilder::build_random() {
	Vector<Company> companies;
	Vector<Trader> traders;

	CompanyBuilder company_builder(this->rng);

	std::cout << "Creating companies: " << std::endl;

	for (usize ii = 0; ii < this->config.get_company_count(); ++ii) {
		companies.push_back(company_builder.build_random(ii));
		companies[ii].print_debug(std::cout);
	}

	Exchange exch(this->rng, this->config, companies, traders);
	return exch;
}
