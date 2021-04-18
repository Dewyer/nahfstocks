#pragma once

#include "../memory/Rc.h"

namespace nhflib {
	template<typename T>
	class Option {
		Rc <T> value;

	public:
		Option() {
			this->reset();
		}


		explicit Option(T value) {
			this->swap(value);
		}

		void reset() noexcept {
			this->value = nullptr;
		}

		void swap(T with_value) noexcept {
			this->value = Rc<T>::make_rc(with_value);
		}

		T &unwrap() {
			if (this->value == nullptr) {
				throw std::runtime_error("Bad option access!");
			}
			return *value;
		}

		const T &unwrap() const {
			if (this->value == nullptr) {
				throw std::runtime_error("Bad option access!");
			}
			return *value;
		}

		T &unwrap_or(T &secondary) noexcept {
			if (this->value == nullptr) {
				return secondary;
			}
			return *value;
		}

		const T &unwrap_or(const T &secondary) const noexcept {
			if (this->value == nullptr) {
				return secondary;
			}
			return *value;
		}

		bool is_some() const noexcept {
			return this->value != nullptr;
		}

		explicit operator bool() const {
			return this->is_some();
		}
	};
}


