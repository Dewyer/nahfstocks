#pragma once

#include "../../trader/TraderAgent.h"
#include "../../../lib/string/String.h"
#include "../../../lib/collections/Vector.h"
#include "../../../lib/memory/Rc.h"
#include "../../../lib/rand/RandomProvider.h"
#include "../../../lib/types.h"
#include "./Order.h"

using nhflib::String;
using nhflib::Vector;
using nhflib::Rc;
using trader::TraderAgent;

namespace exchange {
	struct TraderStock {
		usize company_id;
		usize amount;
		usize free_amount;
	};

	class TraderRecordInExchange {
	public:
		usize trader_id;
		Rc<TraderAgent> trader;
		usize cash_balance;
		usize available_balance;
		usize fixed_income;
		Vector<TraderStock> stocks;

		usize next_activation;

		nhflib::Vector<exchange::Order> open_orders;

		TraderRecordInExchange(usize _trader_id, const Rc<TraderAgent> &trader, usize starting_cash,
							   usize _fixed_income) {
			this->trader_id = _trader_id;
			this->trader = trader;
			this->cash_balance = starting_cash;
			this->available_balance = starting_cash;
			this->fixed_income = _fixed_income;
			this->next_activation = 0;
		}

		void add_or_sub_stocks_and_free_stocks(usize company, i32 amount, i32 free_amount) {
			auto existing_rec = this->stocks.find([&company](Rc<TraderStock> stck) {
				return stck->company_id == company;
			});

			if (!existing_rec.is_null()) {
				existing_rec->amount +=
						amount < 0 ? -std::min(-1 * amount, static_cast<i32>(existing_rec->amount)) : amount;
				existing_rec->free_amount +=
						free_amount < 0 ? -std::min(-1 * free_amount, static_cast<i32>(existing_rec->free_amount))
										: free_amount;
				if (existing_rec->amount == 0) {
					this->stocks.filter_in_place([&existing_rec](Rc<TraderStock> stck) {
						return stck->company_id != existing_rec->company_id;
					});
				}
				return;
			}

			if (amount < 0 || free_amount < 0)
				throw std::runtime_error("Trader can't lose stocks he dosen't own, error.");

			if (amount == 0 && free_amount == 0)
				return;

			auto fam = static_cast<usize>(free_amount);
			auto am = static_cast<usize>(amount);
			this->stocks.push_back(TraderStock{
					company,
					am,
					fam
			});
		}

		void next_random_activation(nhflib::Rc<nhflib::RandomProvider> &rng, usize at, usize max) {
			this->next_activation = at + rng->next_usize_normal(1, max, max / 2, max * 0.25);
		}

		void print_debug(std::ostream &os) const noexcept {
			this->trader->print_debug(os);
			os << "| Bal: " << this->cash_balance << ", Inc: " << this->fixed_income << std::endl;
		}
	};
}
