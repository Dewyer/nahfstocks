#include "ExchangeBuilder.h"
#include "../../lib/collections/Vector.h"
#include "../trader/TraderAgent.h"
#include "../company/CompanyBuilder.h"
#include "../company/CompanyAgent.h"
#include "../trader/TraderAgentBuilder.h"

using nhflib::Vector;
using company::CompanyBuilder;
using company::CompanyAgent;

Rc<Exchange> exchange::ExchangeBuilder::build_random() {
	auto companies = this->build_companies();
	std::cout << std::endl;
	auto traders = this->build_trader_agents();
	auto company_agents = ExchangeBuilder::build_trader_agents_for_companies(companies);

	Exchange exch(this->rng, this->config, companies, traders, company_agents);
	return nhflib::make_rc(exch);
}

Rc<Vector<Company>> exchange::ExchangeBuilder::build_companies() {
	CompanyBuilder company_builder(this->rng, this->config);

	std::cout << "Creating companies: " << std::endl;
	auto companies = nhflib::make_rc_ctr<Vector<Company>>();

	for (usize ii = 0; ii < this->config->get_company_count(); ii++) {
		auto cmp = company_builder.build_random(ii);
		cmp->print_debug(std::cout);
		companies->push_back(cmp);
	}

	return companies;
}

Rc<Vector<TraderAgent>> exchange::ExchangeBuilder::build_trader_agents() {
	trader::TraderAgentBuilder trader_builder;

	auto traders = nhflib::make_rc_ctr<Vector<TraderAgent>>();
	std::cout << "Creating traders: " << std::endl;

	for (usize ii = 0; ii < this->config->get_company_count(); ii++) {
		auto agent = trader_builder.build_random();
		agent->print_debug(std::cout);
		traders->push_back(agent);
	}

	return traders;
}

Rc<Vector<CompanyAgent>> exchange::ExchangeBuilder::build_trader_agents_for_companies(Rc<Vector<Company>> companies) {
	auto traders = nhflib::make_rc_ctr<Vector<CompanyAgent>>();
	std::cout << "Creating traders for companies: " << std::endl;

	companies->for_each([this, &traders](Rc<Company> cmp) {
		auto per_share = this->rng->next_usize_normal(1, 5000, 120, 3000);
		auto agent = new company::CompanyAgent(cmp->get_id(), cmp->get_name() + " Trader", per_share);
		agent->print_debug(std::cout);
		auto agent_rc = nhflib::make_rc<CompanyAgent>(agent);
		traders->push_back(agent_rc);
	});

	return traders;
}
