#pragma once

#include <functional>
#include "collections/Vector.h"

using nhflib::Vector;

namespace nhflib {
    namespace algo {
        template<typename From, typename To>
        Vector<To> map(Vector<From> from_vec, std::function<To(From &)> tf) {
            Vector<To> to_vec;

            for (auto &r : from_vec) {
                to_vec.push_back(tf(r));
            }

            return to_vec;
        }
    }
}