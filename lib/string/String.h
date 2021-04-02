#pragma once

#include <iostream>
#include "../types.h"

namespace nhflib {
    class String {
        char *stringData;
        usize len;
    public:

        size_t size() const { return len; }

        const char *c_str() const { return stringData; }

        String(char ch);

        String(const char *p = "");

        String(const String &s1);

        virtual ~String() { delete[] stringData; }

        void printDbg(const char *txt = "") const {
            std::cout << txt << "[" << len << "], "
                      << (stringData ? stringData : "(NULL)") << std::endl;
        }

        String &operator=(const String &rhs_s);

        String operator+(const String &rhs_s) const;

        String operator+(char rhs_c) const { return *this + String(rhs_c); }

        String& operator+=(const String &rhs_s);

        char &operator[](unsigned int idx);

        const char &operator[](unsigned int idx) const;
    };

    std::ostream &operator<<(std::ostream &os, const String &s0);

    std::istream &operator>>(std::istream &is, String &s0);

    inline String operator+(char ch, const String &str) { return String(ch) + str; }
}