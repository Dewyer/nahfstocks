#pragma once
#include "../../lib/prelude.h"
#include "CliHelper.h"
#include "../../lib/option/Option.h"
#include "../../lib/string/String.h"
#include "../../lib/collections/Vector.h"

using nhflib::Vector;
using nhflib::Option;
using nhflib::String;

namespace cli {
	class CliQuestioner {
		CliHelper &cli;
		Vector<String> options;

		bool is_cancelable;
		String question_val;


	public:
		static usize CANCELED_OPTION;

		explicit CliQuestioner(CliHelper &_cli) :
				cli(_cli),
				options(Vector<String>()),
				is_cancelable(false),
				question_val("") {
		}

		CliQuestioner &question(const String &qst) {
			this->question_val = qst;
			return *this;
		}

		CliQuestioner &cancelable() {
			this->is_cancelable = true;

			return *this;
		}

		CliQuestioner &option(const String &opt_val) {
			this->options.push_back(opt_val);
			return *this;
		}

		usize ask_loop() {
			while (true) {
				auto res = this->ask();
				if (res.is_some()) {
					return res.unwrap();
				}
			}
		}

		Option<usize> ask(bool throw_on_invalid_input = false) {
			this->cli.print_ln(this->question_val);

			if (this->options.size() == 0) {
				this->cli.print_ln("-No options-");
				return Option<usize>();
			}

			for (usize ii = 0; ii < this->options.size(); ii++) {
				auto at_qst = this->options.at(ii);

				this->cli.os() << "- [" << (ii + 1) << "] " << at_qst->c_str();
				this->cli.print_ln();
			}

			if (this->is_cancelable) {
				this->cli.print_ln("- [0] Cancel");
			}

			auto res_opt = this->cli.read_safe_inst<int>();
			if (!res_opt) {
				this->cli.print_ln("Invalid input given.");

				if (throw_on_invalid_input) {
					throw std::runtime_error("Invalid input given.");
				}
				return Option<usize>();
			}
			auto res = res_opt.unwrap();

			auto res_lower_then_max = res <= (int) this->options.size();
			if (res_lower_then_max && ((this->is_cancelable && res >= 0) || res > 0)) {
				return Option<usize>((usize) res);
			}

			this->cli.print_ln("Option picked was invalid.");
			return Option<usize>();
		}
	};
}

