#include "ExchangeBuilder.h"
#include "../../lib/collections/Vector.h"
#include "../../lib/algorithms.h"
#include "../trader/TraderAgent.h"
#include "../company/CompanyBuilder.h"
#include "../trader/TraderAgentBuilder.h"

using nhflib::Vector;
using company::CompanyBuilder;

Rc<Exchange> exchange::ExchangeBuilder::build_random() {
	auto companies = this->build_companies();
	std::cout << std::endl;
	auto traders = this->build_trader_agents();

	Exchange exch(this->rng, this->config, companies, traders);
	return nhflib::make_rc(exch);
}

Rc<Vector<Rc<Company>>> exchange::ExchangeBuilder::build_companies() {
	CompanyBuilder company_builder(this->rng);

	std::cout << "Creating companies: " << std::endl;
	return nhflib::make_rc(nhfalgo::map<usize, Rc<Company>>(
			nhfalgo::range<usize>(this->config->get_company_count()), [&company_builder](const usize &ii) {
				auto cmp = company_builder.build_random(ii);
				cmp->print_debug(std::cout);
				return cmp;
			}));
}

Rc<Vector<Rc<TraderAgent>>> exchange::ExchangeBuilder::build_trader_agents() {
	trader::TraderAgentBuilder trader_builder;

	std::cout << "Creating traders: " << std::endl;
	return nhflib::make_rc(nhfalgo::map<usize, Rc<TraderAgent>>(
			nhfalgo::range(this->config->get_trader_count()),
			[&trader_builder]() {
				auto agent = trader_builder.build_random();
				agent->print_debug(std::cout);
				return agent;
			}
	));
}
