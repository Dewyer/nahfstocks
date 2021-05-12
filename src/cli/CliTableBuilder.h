#pragma once

#include <sstream>
#include "../../lib/prelude.h"
#include "./CliHelper.h"
#include "../../lib/collections/Vector.h"
#include "../../lib/string/String.h"

using nhflib::Vector;
using nhflib::String;

namespace cli {
	enum CliTableCellAlignment {
		Center,
		Left,
		Right
	};

	struct CliTableColumnDefinition {
		String header;
		usize min_characters;
		Option<usize> max_characters;
		Option<CliTableCellAlignment> alignment;

		usize get_width() const {
			return std::max(this->min_characters, this->max_characters.unwrap_or(0));
		}
	};

	struct CliTableCell {
		String cell;
		Option<CliTableCellAlignment> alignment;
	};


	/// Helper to construct tables, with a builder API
	class CliTableBuilder {
		struct CliTableContent {
			String cell;
			CliTableCellAlignment alignment;
			usize width;
		};

		CliHelper &cli;

		usize universal_padding;

		usize at_row_idx;
		usize at_column_idx;
		CliTableCellAlignment default_alignment;

		Vector<CliTableColumnDefinition> columns;
		Vector<Vector<CliTableCell>> rows;

		template<typename T>
		static String cell_to_string(T arg) {
			std::ostringstream str_stream;
			str_stream << arg;
			return String(str_stream.str().c_str());
		}

		void advance_cell_position() {
			this->at_column_idx++;
			if (this->at_column_idx == this->columns.size()) {
				this->at_column_idx = 0;
				this->at_row_idx++;
			}
		}

		void print_decorator_row(Vector<usize> col_lengths) {
			this->cli.print("+");
			for (auto len: col_lengths) {
				for (usize kk = 0; kk < *len; ++kk) {
					this->cli.print("-");
				}
				this->cli.print("+");
			}
			this->cli.print_ln();
		}

		String pad_cell_to_align(CliTableContent content) {
			auto width = content.width;
			auto cell = content.cell.left_pad(' ', this->universal_padding).right_pad(' ', this->universal_padding);
			auto alignment = content.alignment;

			auto width_diff = width - cell.len();
			auto center_pad_right = width_diff % 2 == 0 ? width_diff / 2 : (width_diff - 1) / 2;
			auto center_pad_left = width_diff - center_pad_right;

			switch (alignment) {
				case CliTableCellAlignment::Center:
					return cell.right_pad(' ', center_pad_left).left_pad(' ', center_pad_right);
				case CliTableCellAlignment::Right:
					return cell.left_pad(' ', width_diff);
				default:
					return cell.right_pad(' ', width_diff);
			}
		}

		void print_content_row(Vector<CliTableContent> contents) {
			this->cli.print("|");
			for (auto cont : contents) {
				this->cli.print(this->pad_cell_to_align(*cont));
				this->cli.print("|");
			}
			this->cli.print_ln();
		}

		Vector<usize> get_column_widths() {
			return this->columns.map<usize>([this](Rc<CliTableColumnDefinition> col) {
				return col->get_width() + this->universal_padding * 2;
			});
		}

		void print_column_width_decorator_row() {
			auto widths = this->get_column_widths();
			this->print_decorator_row(widths);
		}

		void print_header() {
			this->print_column_width_decorator_row();

			this->print_content_row(this->columns.map<CliTableContent>([this](Rc<CliTableColumnDefinition> col) {
				return CliTableContent{
						col->header,
						col->alignment.unwrap_or(this->default_alignment),
						col->get_width() + 2 * this->universal_padding,
				};
			}));
		}

		void print_rows() {
			auto widths = this->get_column_widths();
			this->print_column_width_decorator_row();

			for (auto row : this->rows) {
				this->print_content_row(row->map<CliTableContent>([this, &widths](Rc<CliTableCell> cell, usize ii) {
					return CliTableContent{
							cell->cell,
							cell->alignment.unwrap_or(
									this->columns.at(ii)->alignment.unwrap_or(this->default_alignment)),
							*widths.at(ii),
					};
				}));
				this->print_column_width_decorator_row();
			}
		}

	public:
		explicit CliTableBuilder(CliHelper &_cli) :
				cli(_cli) {
			this->columns = Vector<CliTableColumnDefinition>();
			this->rows = Vector<Vector<CliTableCell>>();
			this->at_column_idx = 0;
			this->at_row_idx = 0;
			this->default_alignment = CliTableCellAlignment::Left;
			this->universal_padding = 0;
		}

		CliTableBuilder &default_align(const CliTableCellAlignment &alignment) {
			this->default_alignment = alignment;

			return *this;
		}

		CliTableBuilder &padding(usize pad) {
			this->universal_padding = pad;

			return *this;
		}

		CliTableBuilder &add_column(const String &header, usize min_chars = 0) {
			this->columns.push_back(CliTableColumnDefinition{
					header,
					min_chars,
					Option<usize>(header.len()),
					Option<CliTableCellAlignment>(),
			});

			return *this;
		}

		CliTableBuilder &add_column(const String &header, CliTableCellAlignment alignment, usize min_chars = 0) {
			this->columns.push_back(CliTableColumnDefinition{
					header,
					min_chars,
					Option<usize>(header.len()),
					Option<CliTableCellAlignment>(alignment),
			});

			return *this;
		}

		CliTableBuilder &add_string_cell(const String &str_cell, const Option<CliTableCellAlignment> &alignment) {
			auto column_df = this->columns.at(this->at_column_idx);

			if (!column_df->max_characters || column_df->max_characters.unwrap_or(0) < str_cell.len()) {
				column_df->max_characters = Option<usize>(str_cell.len());
			}
			if (this->rows.size() <= this->at_row_idx) {
				this->rows.push_back(Vector<CliTableCell>());
			}

			this->rows.at(this->rows.size() - 1)->push_back(CliTableCell{
					str_cell,
					alignment
			});

			this->advance_cell_position();
			return *this;
		}

		CliTableBuilder &add_string_cell(const String &str_cell, CliTableCellAlignment alignment) {
			return this->add_string_cell(str_cell, Option<CliTableCellAlignment>(alignment));
		}

		CliTableBuilder &add_string_cell(const String &str_cell) {
			return this->add_string_cell(str_cell, Option<CliTableCellAlignment>());
		}

		template<typename T>
		CliTableBuilder &add_cell(T arg, CliTableCellAlignment alignment) {
			auto str_cell = CliTableBuilder::cell_to_string(arg);
			return this->add_string_cell(str_cell, alignment);
		}

		template<typename T>
		CliTableBuilder &add_cell(T arg) {
			auto str_cell = CliTableBuilder::cell_to_string(arg);
			return this->add_string_cell(str_cell);
		}

		void print() {
			this->print_header();
			this->print_rows();
		}
	};
}

