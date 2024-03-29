#pragma once

#include "../prelude.h"
#include <iostream>
#include <cstring>
#include "../types.h"
#include "../collections/Vector.h"
#include "../memory/Rc.h"
#include "../external/memtrace.h"

using nhflib::Vector;
using nhflib::Rc;

namespace nhflib {
	/// Basic String implementation, works with cstrings under the hood
	class String {
		char *stringData;
		usize length;

		static bool str_cmp(const char *aa, const char *bb) {
			return std::strcmp(aa, bb) == 0;
		}

	public:

		usize len() const { return length; }

		const char *c_str() const { return stringData; }

		String(char ch);

		String(const char *p = "");

		String(const String &s1);

		virtual ~String() { delete[] stringData; }

		Rc<Vector<String>> split(char by_char) const;

		String trim() const;

		String &operator=(const String &rhs_s);

		String operator+(const String &rhs_s) const;

		String operator+(char rhs_c) const { return *this + String(rhs_c); }

		String &operator+=(const String &rhs_s);

		const char &at(usize idx) const;

		char &operator[](unsigned int idx);

		const char &operator[](unsigned int idx) const;

		bool operator==(const String &rsd) const {
			return String::str_cmp(this->c_str(), rsd.c_str());
		}

		bool operator!=(const String &rsd) const {
			return !String::str_cmp(this->c_str(), rsd.c_str());
		}

		bool operator==(const char *rsd) const {
			return String::str_cmp(this->c_str(), rsd);
		}

		bool operator!=(const char *rsd) const {
			return !String::str_cmp(this->c_str(), rsd);
		}

		String left_pad(char cc, usize count) const;

		String right_pad(char cc, usize count) const;
	};
}

std::ostream &operator<<(std::ostream &os, const nhflib::String &s0);

std::istream &operator>>(std::istream &is, nhflib::String &s0);

inline nhflib::String operator+(char ch, const nhflib::String &str) { return nhflib::String(ch) + str; }
