#pragma once

#include "../../lib/string/String.h"
#include "../../lib/collections/Vector.h"
#include "../exchange/exchange_api/Order.h"
#include "../exchange/Exchange.h"
#include "../../lib/memory/Rc.h"
#include "../../lib/option/Option.h"

using nhflib::String;
using nhflib::Option;
using nhflib::Rc;

namespace exchange {
	class Exchange;
}

namespace company {
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

		nhflib::Vector<exchange::Order> orders;

		Option<usize> cached_bid;
		Option<usize> cached_ask;

		Option<usize> bid;
		Option<usize> ask;

		void add_order(nhflib::Rc<exchange::Order> ord_rc);

		void recalculate_bid_ask();

	public:
		Company(usize id, const String &_name, const String &_sym, f64 _financial_standing, f64 _sector,
				f64 _leadership_bias, usize _earnings_offset, usize outstanding_shares);

		usize get_id() const noexcept;

		void print_debug(std::ostream &os) const noexcept;

		const String &get_symbol() const noexcept;

		const String &get_name() const noexcept;

		const Option<usize> &get_bid() const;

		const Option<usize> &get_ask() const;

		f64 get_sector() const noexcept;

		usize get_outstanding_shares() const noexcept;
	};
}
