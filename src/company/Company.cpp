#include "../../lib/prelude.h"
#include "Company.h"
#include "../../lib/string/String.h"
#include "../../lib/types.h"
#include "../utils/format_money.h"
#include "../cli/CliQuestioner.h"

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
						  usize _earnings_offset, usize _outstanding_shares, f64 _dividend_percentage) {
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
	this->price_records = Vector<CompanyPriceRecord>();
	this->dividend_percentage = _dividend_percentage;
}

void company::Company::print_to(Rc<CliHelper> cli) const {
	auto cap_str = utils::format_money(this->get_market_cap());
	auto price_str = utils::format_money(this->get_stock_price());

	cli->os() << "=[" << this->id << "]= " << this->get_name().c_str() << " - [" << this->get_symbol().c_str()
			  << "] Cap: " << cap_str << ", Price: " << price_str;
	cli->print_ln();
	cli->os() << "Sector: " << this->get_sector() << ", Financials: " << this->financial_standing << ", Leadership: "
			  << this->leadership_bias;
	cli->print_ln();
}

usize company::Company::get_id() const noexcept {
	return this->id;
}

void company::Company::add_order(nhflib::Rc<exchange::Order> ord_rc) {
	this->orders.sorted_push_back(ord_rc, [](const Rc<exchange::Order> &then, Rc<exchange::Order> that) {
		if (then->target_price == that->target_price) {
			return then->amount > that->amount;
		}

		return then->target_price < that->target_price;
	});

	if (ord_rc->type == exchange::OrderType::Buy) {
		if (!this->cached_bid.is_some() || this->cached_bid.unwrap() < ord_rc->target_price) {
			this->cached_bid.swap(ord_rc->target_price);
		}

		this->cached_buy_vol += ord_rc->amount;
	}

	if (ord_rc->type == exchange::OrderType::Sell) {
		if (!this->cached_ask.is_some() || this->cached_ask.unwrap() > ord_rc->target_price) {
			this->cached_ask.swap(ord_rc->target_price);
		}

		this->cached_sell_vol += ord_rc->amount;
	}
}

void company::Company::recalculate_details() {
	this->bid = this->cached_bid;
	this->ask = this->cached_ask;
	this->buy_vol = this->cached_buy_vol;
	this->sell_vol = this->cached_sell_vol;
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
	auto price_mid = ask_pr + bid_pr / 2;

	return price_mid;
}

void company::Company::detailed_print_to(Rc<CliHelper> cli) {
	this->print_to(cli);

	cli->os() << "Bid: " << utils::format_money(this->bid.unwrap_or(0))
			  << ", Ask: " << utils::format_money(this->ask.unwrap_or(0));
	cli->print_ln();

	this->view_price_table(cli);
}

void company::Company::take_price_sample(usize cycle) {
	this->price_records.push_back(CompanyPriceRecord{
			cycle,
			this->bid.unwrap_or(0),
			this->ask.unwrap_or(0),
	});
}

void company::Company::view_price_table(Rc<CliHelper> cli) {
	if (this->price_records.size() == 0) {
		cli->print_ln("No pricing records to show.");
		return;
	}
	auto last_record_idx = this->price_records.size() - 1;
	const usize step = 50;
	usize from = 0;
	usize to = std::min(step, last_record_idx);

	while (true) {
		this->view_price_table_in_range(cli, from, to);

		if (to == last_record_idx) {
			break;
		}

		auto qst = cli->build_question()
				.question("Do you want to view the next page?")
				.option("Yes")
				.option("No")
				.ask();

		if (qst.unwrap_or(2) != 1) {
			break;
		}

		auto next_to = std::min(to + step, last_record_idx);
		from += next_to - to;
		to = next_to;
	}
}

void company::Company::view_price_table_in_range(Rc<CliHelper> cli, usize from_idx, usize to_idx) {
	auto record_count = this->price_records.size();
	if (record_count == 0) {
		throw std::runtime_error("No pricing records to show.");
	}

	auto range_ok = record_count - 1 >= from_idx && to_idx >= from_idx && to_idx <= record_count - 1;
	if (!range_ok) {
		throw std::runtime_error("Invalid view for price table.");
	}

	auto price_table = cli->build_table();

	price_table
			.padding(1)
			.add_column("Cycle")
			.add_column("Bid")
			.add_column("Ask");

	for (usize ii = from_idx; ii <= to_idx; ii++) {
		auto pr_el = this->price_records.at(record_count - ii - 1);
		price_table
				.add_cell(pr_el->cycle)
				.add_cell(pr_el->bid)
				.add_cell(pr_el->ask);
	}

	price_table.print();
}

f64 company::Company::get_leadership() const noexcept {
	return this->leadership_bias;
}

f64 company::Company::get_financials() const noexcept {
	return this->financial_standing;
}

bool company::Company::get_had_an_ipo() const noexcept {
	return this->had_an_ipo;
}

usize company::Company::get_buy_vol() const {
	return this->buy_vol;
}

usize company::Company::get_sel_vol() const {
	return this->sell_vol;
}

void company::Company::dump_json(Rc<CliHelper> cli) {
	cli->os() << "{ symbol: \"" << this->get_symbol() << "\" ,prices: [";
	for (usize ii = 0; ii < this->price_records.size(); ii++) {
		auto pr = this->price_records.at(ii);
		cli->os() << "{ ask:" << pr->ask << ", bid: " << pr->bid << "}";

		if (ii != this->price_records.size() - 1) {
			cli->print(",");
		}
	}
	cli->print("]}");
}

usize company::Company::dividend_per_share() const {
	return (usize)std::floor(this->dividend_percentage * this->get_stock_price());
}
