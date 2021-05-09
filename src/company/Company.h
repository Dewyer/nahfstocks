#pragma once
#include "../../lib/prelude.h"
#include "../../lib/string/String.h"
#include "../../lib/collections/Vector.h"
#include "../exchange/exchange_api/Order.h"
#include "../exchange/Exchange.h"
#include "../../lib/memory/Rc.h"
#include "../../lib/option/Option.h"
#include "../cli/CliHelper.h"

using cli::CliHelper;
using nhflib::String;
using nhflib::Option;
using nhflib::Vector;
using exchange::Order;
using nhflib::Rc;

namespace exchange {
	class Exchange;
}

namespace company {
	struct CompanyPriceRecord {
		usize cycle;
		usize bid;
		usize ask;
	};

	class Company {
	private:
		friend class exchange::Exchange;

		usize id;
		String name;
		String symbol;
		f64 financial_standing;
		f64 sector;
		f64 leadership_bias;
		usize earnings_offset;

		usize outstanding_shares;

		Vector<Order> orders;

		Option<usize> cached_bid;
		Option<usize> cached_ask;

		Option<usize> bid;
		Option<usize> ask;

		Vector<CompanyPriceRecord> price_records;

		void add_order(nhflib::Rc<exchange::Order> ord_rc);

		void recalculate_bid_ask();

		void view_price_table_in_range(Rc<CliHelper> cli, usize from_idx, usize to_idx);

		void view_price_table(Rc<CliHelper> cli);

	public:
		Company(usize id, const String &_name, const String &_sym, f64 _financial_standing, f64 _sector,
				f64 _leadership_bias, usize _earnings_offset, usize outstanding_shares);

		usize get_id() const noexcept;

		void print_to(Rc<CliHelper> cli) const;

		void detailed_print_to(Rc<CliHelper> cli);

		usize get_market_cap() const;

		usize get_stock_price() const;

		const String &get_symbol() const noexcept;

		const String &get_name() const noexcept;

		const Option<usize> &get_bid() const;

		const Option<usize> &get_ask() const;

		f64 get_sector() const noexcept;

		usize get_outstanding_shares() const noexcept;

		void take_price_sample(usize cycle);
	};
}
