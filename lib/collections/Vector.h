#pragma once
#include <vector>
#include "../types.h"

namespace nhflib {
	template<typename T>
	class Vector {
	private:
		std::vector<T> inner;

	public:
		void push_back(T el);

		usize size() const noexcept;
	};
};
