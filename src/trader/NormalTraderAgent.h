#pragma once
#include "./TraderAgent.h"
#include "../../lib/memory/Rc.h"
#include "../../lib/collections/Vector.h"
#include "../../lib/string/String.h"
#include "../../lib/rand/RandomProvider.h"

using nhflib::String;
using nhflib::RandomProvider;
using nhflib::Rc;

namespace trader {
	struct TraderCompanyProfile {
		f64 sentiment;
	};

	class NormalTraderAgent : public TraderAgent {
		Rc<RandomProvider> rng;
		f64 finance_bias;
		f64 leadership_bias;
		f64 sector_focus;
		f64 focus_sector_threshold;
		f64 volume_sensitivity;
		f64 price_sensitivity;

		Vector<TraderCompanyProfile> profiles;

		void choose_random_settings();

	public:
		NormalTraderAgent(const String& _name, const Rc<RandomProvider>& _rng): TraderAgent(_name) {
			this->rng = _rng;
			this->profiles = Vector<TraderCompanyProfile>();

			this->choose_random_settings();
		}

		virtual void init(TraderAgentInitPayload payload) override;

		void on_cycle(exchange::ExchangeApi &api) override;
	};

}