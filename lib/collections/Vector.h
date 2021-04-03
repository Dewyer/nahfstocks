#pragma once

#include <vector>
#include "../types.h"

namespace nhflib {
    template<typename T>
    class Vector {
    private:
        std::vector<T> inner;

    public:
        void push_back(T el) {
            this->inner.push_back(el);
        }

        usize size() const noexcept {
            return this->inner.size();
        }

        typename std::vector<T>::iterator begin() {
            return this->inner.begin();
        }

        typename std::vector<T>::iterator end() {
            return this->inner.end();

        }

        T &operator[](usize idx) {
            return this->inner[idx];
        }

        const T &operator[](usize idx) const {
            return this->inner[idx];
        }
    };
}

template<typename T>
typename std::vector<T>::iterator begin(nhflib::Vector<T> vec) {
    return vec.begin();
}

template<typename T>
typename std::vector<T>::iterator end(nhflib::Vector<T> vec) {
    return vec.end();
}