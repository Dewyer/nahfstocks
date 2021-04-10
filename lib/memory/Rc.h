#pragma once

#include "../types.h"

namespace nhflib {
	template<typename T>
	class Rc {
	private:
		T *data_ptr;
		usize *ref_count;

		void initialize(T *dat, usize *rc) {
			this->data_ptr = dat;
			this->ref_count = rc;

		}

		void nullize() {
			this->initialize(nullptr, nullptr);
		}

		void copy(T *dat, usize *rc) {
			this->initialize(dat, rc);
			if (this->is_null()) {
				return;
			}

			(*this->ref_count)++;
		}

	public:
		Rc() {
			this->nullize();
		}

		Rc(nullptr_t nptr) {
			this->initialize(nptr, nptr);
		}

		Rc(T *from) {
			this->initialize(from, new usize(1));
		}

		Rc(const Rc<T> &copy_from) {
			this->copy(copy_from.data_ptr, copy_from.ref_count);
		}

		Rc<T> &operator=(const Rc<T> &rhs) {
			if (this == &rhs) {
				return *this;
			}

			if (rhs.is_null()) {
				this->free();
			}

			this->copy(rhs.data_ptr, rhs.ref_count);

			return *this;
		}

		~Rc() {
			this->free();
		}

		static Rc<T> make_rc(T from_t) {
			Rc<T> temp(new T(from_t));
			return temp;
		}

		static Rc<T> make_rc(T *from_t) {
			Rc<T> temp(from_t);
			return temp;
		}

		T *operator->() {
			return this->data_ptr;
		}

		T &operator*() {
			return *this->data_ptr;
		}

		const T &operator*() const {
			return *this->data_ptr;
		}

		const T *operator->() const {
			return this->data_ptr;
		}

		bool operator==(const T* rhs) const {
			return this->data_ptr == rhs;
		}

		bool operator!=(const T* rhs) const {
			return this->data_ptr != rhs;
		}

		bool operator==(const Rc<T>& rhs) const {
			return this->data_ptr == rhs.data_ptr;
		}

		bool operator!=(const Rc<T>& rhs) const {
			return this->data_ptr != rhs.data_ptr;
		}

		void free() {
			if (this->is_null()) {
				return;
			}

			--(*this->ref_count);
			if (*this->ref_count == 0) {
				delete this->data_ptr;
				delete this->ref_count;
			}
			this->nullize();
		}

		inline bool is_null() const {
			return this->data_ptr == nullptr || this->ref_count == nullptr;
		}
	};
}