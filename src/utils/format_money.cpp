#include "./format_money.h"
#include "./to_string.h"

String utils::format_money(usize money) {
	String res;
	auto money_str = utils::to_string(money);

	for (usize ii = 0; ii < money_str.len(); ii++) {
		auto at_digit = money_str[money_str.len() - ii - 1];
		res = at_digit + res;

		if ((ii + 1) % 3 == 0 && ii != money_str.len() - 1) {
			res = ',' + res;
		}
	}
	res = '$' + res;
	return res;
}