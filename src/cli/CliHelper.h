#pragma once

#include "../../lib/option/Option.h"
#include "../../lib/string/String.h"
#include "limits"

using nhflib::String;
using nhflib::Option;

namespace cli {
	class CliQuestioner;

	class CliHelper {
		std::ostream* out_stream;
		std::istream* in_stream;

	public:
		CliHelper(std::ostream* _out_stream=&std::cout, std::istream* _in_stream=&std::cin) :
		out_stream(_out_stream),
		in_stream(_in_stream)
		{}

		static void ignore_last_inf_chars(std::istream &inp = std::cin) {
			inp.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		template<typename TInp>
		static Option<TInp> read_safe(std::istream &inp = std::cin) {
			TInp inp_res;
			auto failed = !(inp >> std::noskipws >> inp_res);

			if (inp.fail() || failed) {
				inp.clear();
				CliHelper::ignore_last_inf_chars(inp);
				return Option<TInp>();
			}

			CliHelper::ignore_last_inf_chars(inp);
			return Option<TInp>(inp_res);
		}

		template<typename TInp>
		Option<TInp> read_safe_inst() {
			return CliHelper::read_safe<TInp>(*this->in_stream);
		}

		CliQuestioner build_question();

		template<typename TOut>
		void print(const TOut& dat) {
			if (this->out_stream) {
				(*this->out_stream) << dat;
			}
		}

		template<typename TOut>
		void print_ln(const TOut& dat) {
			this->print(dat);
			if (this->out_stream) {
				(*this->out_stream) << std::endl;
			}
		}

		void print_ln() {
			if (this->out_stream) {
				(*this->out_stream) << std::endl;
			}
		}

		CliHelper& os() {
			return *this;
		}

		template<typename TOut>
		CliHelper& operator<<(TOut tt) {
			this->print(tt);
			return *this;
		}

	};
}