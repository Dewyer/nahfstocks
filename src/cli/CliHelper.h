#pragma once

#include "../../lib/option/Option.h"
#include "limits"

using nhflib::Option;

namespace cli {
	class CliHelper {
	public:
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

	};
}