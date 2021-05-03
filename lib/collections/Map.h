#pragma once

#include "../types.h"
#include "../collections/Vector.h"
#include "../memory/Rc.h"
#include "../option/Option.h"

using nhflib::Option;
using nhflib::Vector;
using nhflib::Rc;

namespace nhflib {
	template<typename TKey, typename TVal>
	class Map {
	private:
		Vector<TKey> keys;
		Vector<TVal> values;

	public:
		bool has(const TKey &key) const {
			return this->keys.some([&key](Rc<TKey> el) {
				return *el == key;
			});
		}

		void insert(const TKey &key, TVal val) {
			this->keys.push_back(key);
			this->values.push_back(val);
		}

		void clear() {
			this->keys.clear();
			this->values.clear();
		}

		Option<Rc<TVal>> get(const TKey &key) {
			auto val_ind = this->keys.index_of([&key](Rc<TKey> el) {
				return *el == key;
			});

			if (!val_ind || this->values.size() <= val_ind.unwrap()) {
				return Option<Rc<TVal>>();
			}

			auto val = this->values.at(val_ind.unwrap());
			return Option<Rc<TVal>>(val);
		}
	};

}