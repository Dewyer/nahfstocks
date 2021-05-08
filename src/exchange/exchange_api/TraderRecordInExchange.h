#pragma once

#include "../../trader/TraderAgent.h"
#include "../../../lib/string/String.h"
#include "../../../lib/collections/Vector.h"
#include "../../../lib/memory/Rc.h"
#include "../../../lib/rand/RandomProvider.h"
#include "../../../lib/types.h"
#include "../../cli/CliHelper.h"
#include "./Order.h"
#include "../../utils/format_money.h"
#include "../../cli/CliTableBuilder.h"

using cli::CliHelper;
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

	struct CompanyDto {
		String symbol;
		String name;
		usize price;

		static CompanyDto empty() {
			return CompanyDto{
					"N/A",
					"N/A",
					0
			};
		}
	};

	class TraderRecordInExchange {
	public:
		usize trader_id;
		Rc<TraderAgent> trader;
		usize total_balance;
		usize available_balance;
		usize fixed_income;
		Vector<TraderStock> stocks;

		usize next_activation;

		Vector<Order> open_orders;

		typedef std::function<CompanyDto(usize)> CompanyDtoLookupFn;

		TraderRecordInExchange(usize _trader_id, const Rc<TraderAgent> &trader, usize starting_cash,
							   usize _fixed_income) {
			this->trader_id = _trader_id;
			this->trader = trader;
			this->total_balance = starting_cash;
			this->available_balance = starting_cash;
			this->fixed_income = _fixed_income;
			this->next_activation = 0;
			this->open_orders = Vector<exchange::Order>();
		}

		usize get_locked_balance() const {
			return this->total_balance - this->available_balance;
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

		void print_to(Rc<CliHelper> cli) const noexcept {
			this->trader->print_to(cli);
			cli->os() << "| Bal: " << utils::format_money(this->total_balance) << ", Inc: "
					  << utils::format_money(this->fixed_income);
			cli->print_ln();
		}


		void detailed_print_to(Rc<CliHelper> cli, const CompanyDtoLookupFn &lookup_company_dto) {
			this->print_to(cli);
			this->detailed_print_orders(cli, lookup_company_dto);
			this->detailed_print_portfolio(cli, lookup_company_dto);
		}

	private:

		void detailed_print_orders(Rc<CliHelper> cli, const CompanyDtoLookupFn &lookup_company_data) {
			cli->os() << "Locked balance: " << utils::format_money(this->get_locked_balance()) << ", Orders: ";
			cli->print_ln();

			auto orders_table = cli->build_table();
			orders_table
					.add_column("ID")
					.add_column("Type")
					.add_column("Company")
					.add_column("Amount")
					.add_column("Price")
					.add_column("Total Price");

			orders_table.padding(1);

			for (auto order : this->open_orders) {
				auto company_dto = lookup_company_data(order->company_id);
				orders_table
						.add_cell(order->id, cli::CliTableCellAlignment::Right)
						.add_cell(exchange::order_type_to_string(order->type))
						.add_cell(company_dto.symbol)
						.add_cell(order->amount)
						.add_cell(utils::format_money(order->target_price))
						.add_cell(utils::format_money(order->get_total_price()));
			}

			orders_table.print();
			cli->print_ln();
		}

		void detailed_print_portfolio(Rc<CliHelper> cli, const CompanyDtoLookupFn &lookup_company_data) {
			auto portfolio_worth = 0;
			auto portfolio_table = cli->build_table();
			portfolio_table
					.padding(1)
					.default_align(cli::CliTableCellAlignment::Right)
					.add_column("Company", cli::CliTableCellAlignment::Center)
					.add_column("Shares")
					.add_column("Total Value");

			for (auto stock : this->stocks) {
				auto company_dto = lookup_company_data(stock->company_id);
				auto shares_value = stock->amount * company_dto.price;
				portfolio_table
						.add_cell(company_dto.symbol)
						.add_cell(stock->amount)
						.add_cell(shares_value);

				portfolio_worth += shares_value;
			}

			cli->os() << "Portfolio's worth: " << utils::format_money(portfolio_worth);
			cli->print_ln();
			portfolio_table.print();
			cli->print_ln();
		}

	};
}
