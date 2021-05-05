#pragma once

#include <vector>
#include "../memory/Rc.h"
#include "../option/Option.h"
#include "../types.h"

namespace nhflib {
	template<typename T>
	class Vector {
	private:
		Rc<T> *data;
		usize len;
		usize capacity;

		void null_init() {
			this->data = nullptr;
			this->len = 0;
			this->capacity = 0;
		}

		void resize(usize to) {
			auto temp = this->data;
			this->data = new Rc<T>[to];
			for (usize ii = 0; ii < std::min(this->size(), to); ii++) {
				this->data[ii] = temp[ii];
			}
			if (temp != nullptr) {
				delete[] temp;
			}

			this->capacity = to;
		}

		void copy(const Vector<T> &rhs) {
			this->null_init();
			this->resize(rhs.len);
			this->len = rhs.len;
			for (usize ii = 0; ii < this->size(); ii++) {
				this->data[ii] = rhs.at(ii);
			}
		}

		void assert_index_in_bound(usize ii) {
			if (this->len <= ii) {
				throw std::runtime_error("Index out of bounds of vector");
			}
		}

	public:
		Vector() {
			this->null_init();
		}

		Vector(const Vector<T> &rhs) {
			this->copy(rhs);
		}

		Vector<T> &operator=(const Vector<T> &rhs) {
			if (this == &rhs) {
				return *this;
			}

			this->copy(rhs);
			return *this;
		}

		~Vector() {
			if (this->data == nullptr) {
				return;
			}

			delete[] this->data;
		}

		void clear() {
			if (this->data != nullptr) {
				delete[] this->data;
			}

			this->null_init();
		}

		void push_back(const Rc<T> &el) {
			if (this->capacity < this->len + 1) {
				this->resize(this->len + 1);
			}

			this->data[this->len] = el;
			this->len++;
		}

		void push_back(T *el) {
			this->push_back(make_rc(el));
		}

		void push_back(T el) {
			this->push_back(make_rc(el));
		}

		void remove_at(usize ind) {
			this->assert_index_in_bound(ind);
			if (this->size() == 1) {
				this->clear();
				return;
			}

			auto temp = this->data;
			this->data = new Rc<T>[this->size() - 1];
			for (usize ii = 0; ii < ind; ii++) {
				this->data[ii] = temp[ii];
			}
			for (usize ii = ind + 1; ii < this->size(); ii++) {
				this->data[ii - 1] = temp[ii];
			}
			delete[] temp;

			this->len--;
			this->capacity = this->size() - 1;
		}

		void insert_at(usize idx, const Rc<T> &el) {
			if (this->len >= idx) {
				this->push_back(el);
				return;
			}

			auto temp = data;
			this->data = new Rc<T>[this->size() + 1];
			for (usize ii = 0; ii < idx; ii++) {
				this->data[ii] = temp[ii];
			}
			this->data[idx] = el;
			for (usize ii = idx + 1; ii < this->size(); ii++) {
				this->data[ii + 1] = temp[ii];
			}
			delete[] temp;

			this->len++;
			this->capacity = this->size() + 1;
		}

		template<typename S>
		void filter_in_place(S filter_fn) {
			Vector<T> matches;
			for (usize ii = 0; ii < this->size(); ii++) {
				auto at_el = this->at(ii);
				if (filter_fn(at_el)) {
					matches.push_back(at_el);
				}
			}

			this->clear();
			this->data = matches.data;
			this->len = matches.len;
			this->capacity = matches.capacity;
			matches.null_init();
		}

		template<typename S>
		bool remove(S som_fn) {
			for (usize ii = 0; ii < this->size(); ii++) {
				if (som_fn(this->at(ii))) {
					this->remove_at(ii);
					return true;
				}
			}

			return false;
		}


		template<typename S>
		void sorted_push_back(const Rc<T> &el, S el_bigger) {
			for (usize ii = 0; ii < this->size(); ii++) {
				auto el_ii = this->at(ii);
				if (el_bigger(el, el_ii)) {
					this->insert_at(ii + 1, el);
					return;
				}
			}

			this->push_back(el);
		}

		template<typename S>
		Option<usize> index_of(S index_fn) {
			for (usize ii = 0; ii < this->size(); ii++) {
				if (index_fn(this->at(ii))) {
					return Option<usize>(ii);
				}
			}

			return Option<usize>();
		}

		template<typename S>
		bool some(S som_fn) const {
			for (usize ii = 0; ii < this->size(); ii++) {
				if (som_fn(this->at(ii))) {
					return true;
				}
			}

			return false;
		}

		template<typename S>
		Rc<T> find(S find_fn) {
			for (usize ii = 0; ii < this->size(); ii++) {
				if (find_fn(this->at(ii))) {
					return this->at(ii);
				}
			}

			return Rc<T>(nullptr);
		}

		template<typename S>
		Rc<T> max(S max_fn) {
			auto max_now = nhflib::make_rc<T>();

			for (usize ii = 0; ii < this->size(); ii++) {
				auto el = this->at(ii);
				if (!max_now) {
					max_now = el;
					continue;;
				}

				if (max_fn(el) > max_fn(max_now)) {
					max_now = el;
				}
			}

			return max_now;
		}

		usize size() const noexcept {
			return this->len;
		}

		Rc<T> at(usize idx) {
			this->assert_index_in_bound(idx);
			return this->data[idx];
		}

		const Rc<T> at(usize idx) const {
			return this->data[idx];
		}

		Rc<T> operator[](usize idx) {
			return this->at(idx);
		}

		const Rc<T> operator[](usize idx) const {
			return this->at(idx);
		}

		Vector<T> clone() const {
			Vector<T> vec;
			for (usize ii = 0; ii < this->size(); ii++) {
				auto el = this->at(ii);
				vec.push_back(el.clone());
			}

			return vec;
		}

		Vector<T> concat(const Vector<T> &second) const {
			Vector<T> vec;
			for (usize ii = 0; ii < this->size(); ii++) {
				auto el = this->at(ii);
				vec.push_back(el.clone());
			}

			for (usize kk = 0; kk < second.size(); kk++) {
				auto el = second.at(kk);
				vec.push_back(el.clone());
			}

			return vec;
		}

		template<typename S>
		void for_each(S fn) {
			for (usize ii = 0; ii < this->size(); ii++) {
				fn(this->at(ii));
			}
		}
	};
}
