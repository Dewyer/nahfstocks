#pragma once

#include <functional>
#include "collections/Vector.h"

using nhflib::Vector;

namespace nhfalgo {
	template<typename From, typename To>
	Vector<To> map(const Vector<From> &from_vec, std::function<To(const From &)> tf) {
		Vector<To> to_vec;

		for (usize ii = 0; ii < from_vec.size(); ii++) {
			to_vec.push_back(tf(from_vec[ii]));
		}

		return to_vec;
	}

	template<typename From, typename To>
	Vector<To> map(const Vector<From> &from_vec, std::function<To()> tf) {
		Vector<To> to_vec;

		for (usize ii = 0; ii < from_vec.size(); ii++) {
			to_vec.push_back(tf());
		}

		return to_vec;
	}

	template<typename NumType>
	Vector<NumType> range(NumType from, NumType to) {
		Vector<NumType> range_v;
		for (NumType ii = from; ii < to; ii++) {
			range_v.push_back(ii);
		}

		return range_v;
	}

	template<typename NumType>
	Vector<NumType> range(NumType to) {
		Vector<NumType> range_v;
		for (NumType ii = 0; ii < to; ii++) {
			range_v.push_back(ii);
		}

		return range_v;
	}
}