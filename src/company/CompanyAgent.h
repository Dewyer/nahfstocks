#pragma once

#include "../../lib/prelude.h"
#include "../trader/TraderAgent.h"
#include "../../lib/string/String.h"

namespace company {
	/// The TraderAgent implementation that helps implement a company IPO
	class CompanyAgent : public trader::TraderAgent {
		usize company_id;
		usize per_share_starter;
	public:
		explicit CompanyAgent(usize _company, const nhflib::String &name, usize _per_share_starter) :
				TraderAgent(name),
				company_id(_company),
				per_share_starter(_per_share_starter) {}


		void on_cycle(exchange::ExchangeApi &api) override;

		usize get_company() const noexcept;
	};
}
