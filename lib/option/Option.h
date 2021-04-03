#pragma once

#include <memory>

namespace nhflib {
    template<typename T>
    class Option {
        std::shared_ptr<T> value;

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
            this->value = std::make_shared<T>(with_value);
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
                throw secondary;
            }
            return *value;
        }

        const T &unwrap_or(T &secondary) const noexcept {
            if (this->value == nullptr) {
                throw secondary;
            }
            return *value;
        }

        bool is_some() const noexcept {
			return this->value != nullptr;
        }

		explicit operator bool () const {
        	return this->is_some();
        }
    };
}


