#pragma once

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
	};

	class Order : public OrderCreationPayload {
	public:
		usize id;
		usize trader_id;

		nhflib::Rc<TraderRecordInExchange> trader;

		Order(usize _id, usize _trader_id, const nhflib::Rc<TraderRecordInExchange> &_trader,
			  const OrderCreationPayload &payload) :
				OrderCreationPayload(payload),
				id(_id),
				trader_id(_trader_id),
				trader(_trader) {
		}
	};

}