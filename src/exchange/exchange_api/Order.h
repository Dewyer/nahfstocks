#pragma once
#include "../../../lib/types.h"

namespace exchange {

	enum OrderType {
		Buy,
		Sell,
	};

	class Order {
	public:
		OrderType type;
		usize trader_id;
		usize company_id;

		usize amount;
		usize target_price;

		usize expires_at;
	};
}