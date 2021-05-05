#include "Company.h"
#include "../../lib/string/String.h"
#include "../../lib/types.h"

using nhflib::Vector;
using nhflib::String;
using exchange::Order;

const String &company::Company::get_name() const noexcept {
	return this->name;
}

f64 company::Company::get_sector() const noexcept {
	return this->sector;
}

const String &company::Company::get_symbol() const noexcept {
	return this->symbol;
}

company::Company::Company(usize id, const String &_name, const String &_sym, f64 _financial_standing, f64 _sector,
						  f64 _leadership_bias,
						  usize _earnings_offset, usize _outstanding_shares) {
	this->id = id;
	this->name = _name;
	this->symbol = _sym;
	this->financial_standing = _financial_standing;
	this->sector = _sector;
	this->leadership_bias = _leadership_bias;
	this->earnings_offset = _earnings_offset;
	this->cached_ask = Option<usize>();
	this->cached_bid = Option<usize>();
	this->bid = Option<usize>();
	this->ask = Option<usize>();
	this->outstanding_shares = _outstanding_shares;
	this->orders = Vector<Order>();
}

void company::Company::print_to(Rc<CliHelper> cli) const noexcept {
	cli->os() << "=[" << this->id << "]= " << this->get_name().c_str() << " - [" << this->get_symbol().c_str() << "] Cap: " << this->get_market_cap() << "$, Price: " << this->get_stock_price() << "$";
	cli->print_ln();
	cli->os() << "Sector: " << this->get_sector() << ", Financials: " << this->financial_standing << ", Leadership: "
	   << this->leadership_bias;
	cli->print_ln();
}

usize company::Company::get_id() const noexcept {
	return this->id;
}


bool sort_orders(Rc<exchange::Order> then, Rc<exchange::Order> that) {
	if (then->target_price == that->target_price) {
		return then->amount > that->amount;
	}

	return then->target_price > that->target_price;
}

void company::Company::add_order(nhflib::Rc<exchange::Order> ord_rc) {
	this->orders.sorted_push_back(ord_rc, sort_orders);
	if (ord_rc->type == exchange::OrderType::Buy) {
		if (!this->cached_bid.is_some() || this->cached_bid.unwrap() < ord_rc->target_price) {
			this->cached_bid.swap(ord_rc->target_price);
		}
	}

	if (ord_rc->type == exchange::OrderType::Sell) {
		if (!this->cached_ask.is_some() || this->cached_ask.unwrap() > ord_rc->target_price) {
			this->cached_ask.swap(ord_rc->target_price);
		}
	}
}

void company::Company::recalculate_bid_ask() {
	this->bid = this->cached_bid;
	this->ask = this->cached_ask;
}

const Option<usize> &company::Company::get_bid() const {
	return this->bid;
}

const Option<usize> &company::Company::get_ask() const {
	return this->ask;
}

usize company::Company::get_outstanding_shares() const noexcept {
	return this->outstanding_shares;
}

usize company::Company::get_market_cap() const {
	auto price = this->get_stock_price();

	return this->outstanding_shares * price;
}

usize company::Company::get_stock_price() const {
	auto ask_pr = this->get_ask().unwrap_or(0);
	auto bid_pr = this->get_bid().unwrap_or(0);
	auto price_mid = ask_pr+bid_pr / 2;

	return price_mid;
}
