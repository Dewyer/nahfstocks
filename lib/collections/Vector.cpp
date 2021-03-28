#include "Vector.h"


template<typename T>
void nhflib::Vector<T>::push_back(T el) {
	this->inner.push_back(el);
}

template<typename T>
usize nhflib::Vector<T>::size() const noexcept {
	return this->inner.size();
}
