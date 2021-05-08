#include "./format_money.h"
#include "math.h"

int pow_ez(int kk, int dd) {
	int rr = 1;
	for (int ii = 0; ii < dd; ++ii) {
		rr *= kk;
	}

	return rr;
}

String utils::format_money(usize money) {
	String res;

	if (money == 0) {
		return "$0";
	}

	auto i_money = (int) money;
	auto left_num = 0;

	for (int ii = 0;; ii++) {
		auto large_mod = pow_ez(10, ii + 1);
		auto small_mod = pow_ez(10, ii);

		auto at_digit = ((i_money % large_mod) - left_num) / small_mod;
		left_num += at_digit * small_mod;

		res = ('0' + at_digit) + res;
		if (i_money == left_num) {
			break;
		}
		if ((ii + 1) % 3 == 0) {
			res = ',' + res;
		}
	}
	res = '$' + res;
	return res;
}