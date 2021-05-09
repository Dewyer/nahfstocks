#pragma once
// Kurwa anyádat memtrace hogy nem tudnak bazmeg az IIT ben programozni összefosom magam
#include <cstddef>
#include <cstdint>
#include <memory>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <utility>
#include <memory>
#include <limits>
#include <functional>
#include <cstdlib>
#include <random>
#include "../prelude.h"
#include "../types.h"
#include "../external/memtrace.h"

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

	public:
		void copy_dangerous(T *dat, usize *rc) {
			this->initialize(dat, rc);
			if (this->is_null()) {
				return;
			}

			(*this->ref_count)++;
		}

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
			this->copy_dangerous(copy_from.data_ptr, copy_from.ref_count);
		}

		Rc<T> &operator=(const Rc<T> &rhs) {
			if (this == &rhs) {
				return *this;
			}

			if (rhs.is_null()) {
				this->fre_ptr();
			}

			this->copy_dangerous(rhs.data_ptr, rhs.ref_count);

			return *this;
		}

		~Rc() {
			this->fre_ptr();
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

		bool operator==(const T *rhs) const {
			return this->data_ptr == rhs;
		}

		bool operator!=(const T *rhs) const {
			return this->data_ptr != rhs;
		}

		bool operator==(const Rc<T> &rhs) const {
			return this->data_ptr == rhs.data_ptr;
		}

		bool operator!=(const Rc<T> &rhs) const {
			return this->data_ptr != rhs.data_ptr;
		}

		operator bool() const {
			return !this->is_null();
		}

		void fre_ptr() {
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

		Rc<T> clone() const {
			return Rc<T>::make_rc(*this->data_ptr);
		}

		template<typename BaseT>
		Rc<BaseT> base_rc() {
			Rc<BaseT> base_rc;
			base_rc.copy_dangerous(static_cast<BaseT *>(this->data_ptr), this->ref_count);
			return base_rc;
		}

		inline bool is_null() const {
			return this->data_ptr == nullptr || this->ref_count == nullptr;
		}
	};

	template<typename T>
	Rc<T> make_rc(T from_t) {
		return Rc<T>::make_rc(from_t);
	}

	template<typename T>
	Rc<T> make_rc(T *from_t) {
		return Rc<T>::make_rc(from_t);
	}

	template<typename T>
	Rc<T> make_rc_ctr() {
		T t;
		return Rc<T>::make_rc(t);
	}

	template<typename T>
	Rc<T> make_rc() {
		Rc<T> rc(nullptr);
		return rc;
	}
}