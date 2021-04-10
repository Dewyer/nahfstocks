#include "ExchangeBuilder.h"
#include "../../lib/collections/Vector.h"
#include "../../lib/algorithms.h"
#include "../trader/TraderAgent.h"
#include "../company/CompanyBuilder.h"
#include "../trader/TraderAgentBuilder.h"

using nhflib::Vector;
using company::CompanyBuilder;

Exchange exchange::ExchangeBuilder::build_random() {
	Vector<Company> companies = this->build_companies();
	std::cout << std::endl;
	Vector<TraderAgent> traders = this->build_trader_agents();

	Exchange exch(this->rng, this->config, companies, traders);
	return exch;
}

Vector<Company> exchange::ExchangeBuilder::build_companies() {
	CompanyBuilder company_builder(this->rng);

	std::cout << "Creating companies: " << std::endl;
	return nhfalgo::map<usize, Company>(
			nhfalgo::range<usize>(this->config->get_company_count()), [&company_builder](usize &ii) {
				Company cmp = company_builder.build_random(ii);
				cmp.print_debug(std::cout);
				return cmp;
			});;
}

Vector<TraderAgent> exchange::ExchangeBuilder::build_trader_agents() {
	trader::TraderAgentBuilder trader_builder;

	std::cout << "Creating traders: " << std::endl;
	return nhfalgo::map<usize, TraderAgent>(
			nhfalgo::range(this->config->get_trader_count()),
			[&trader_builder]() {
				TraderAgent agent = trader_builder.build_random();
				agent.print_debug(std::cout);
				return agent;
			}
	);
}
