#include "ExchangeBuilder.h"
#include "../../lib/collections/Vector.h"
#include "../trader/ITrader.h"
#include "../company/CompanyBuilder.h"

using nhflib::Vector;
using company::CompanyBuilder;

Exchange exchange::ExchangeBuilder::build_random() {
	Vector<Company> companies;
	Vector<ITrader> traders;
	CompanyBuilder company_builder;

	for (usize ii = 0; ii < this->config.get_company_count(); ++ii) {
		companies.push_back()
	}

}
