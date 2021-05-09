#pragma once

#include <utility>

#include "../../../lib/types.h"
#include "../../../lib/memory/Rc.h"
#include "../../../lib/option/Option.h"
#include "../../../lib/string/String.h"

using nhflib::String;

namespace exchange {

	class TraderRecordInExchange;

	enum OrderType {
		Buy,
		Sell,
	};

	String order_type_to_string(const OrderType &type);

	class OrderCreationPayload {
	public:
		OrderType type;
		usize company_id;

		usize amount;
		usize target_price;

		nhflib::Option<usize> expires_at;

		usize get_total_price() const noexcept {
			return this->amount * this->target_price;
		}

		OrderCreationPayload(OrderType type, usize i, usize i1, usize i2, nhflib::Option<usize> option)
		: type(type),
		company_id(i),
		amount(i1),
		target_price(i2),
		expires_at(option)
		{
		}

		virtual ~OrderCreationPayload() = default;
	};

	class Order : public OrderCreationPayload {
	public:
		usize id;
		usize trader_id;

		Order(usize _id, usize _trader_id, const OrderCreationPayload &payload);

		virtual ~Order() = default;
	};

}