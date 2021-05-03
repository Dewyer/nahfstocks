#include "String.h"
#include <iostream>
#include <cstring>

using std::cin;
using std::ios_base;
using nhflib::String;

String::String(char ch) {
	length = 1;
	stringData = new char[length + 1];
	stringData[0] = ch;
	stringData[1] = '\0';
}


String::String(const char *p) {
	length = strlen(p);
	stringData = new char[length + 1];
	strcpy(stringData, p);
}

String::String(const String &s1) {
	length = s1.length;
	stringData = new char[length + 1];
	strcpy(stringData, s1.stringData);
}

String &String::operator=(const String &rhs_s) {
	if (this != &rhs_s) {
		delete[] stringData;
		length = rhs_s.length;
		stringData = new char[length + 1];
		strcpy(stringData, rhs_s.stringData);
	}
	return *this;
}

char &String::operator[](unsigned int idx) {
	if (idx >= length) throw std::out_of_range("String index out of range");
	return stringData[idx];
}

const char &String::operator[](unsigned int idx) const {
	return this->at(idx);
}

String String::operator+(const String &rhs_s) const {
	String temp;
	temp.length = length + rhs_s.length;
	delete[]temp.stringData;
	temp.stringData = new char[temp.length + 1];
	strcpy(temp.stringData, stringData);
	strcat(temp.stringData, rhs_s.stringData);

	return temp;
}

String &nhflib::String::operator+=(const String &rhs_s) {
	this->length = length + rhs_s.length;
	char *saved_own_data = this->stringData;
	this->stringData = new char[this->length + 1];
	strcpy(this->stringData, saved_own_data);
	strcat(this->stringData, rhs_s.stringData);
	delete[] saved_own_data;

	return *this;
}

Rc<Vector<String>> nhflib::String::split(char by_char) const {
	auto res = nhflib::make_rc_ctr<Vector<String>>();
	String last_buf = "";

	if (this->len() == 0) {
		return res;
	}

	for (usize ii = 0; ii < this->len(); ii++) {
		auto at_chr = this->at(ii);
		if (at_chr == by_char) {
			res->push_back(last_buf);
			last_buf = "";
		} else {
			last_buf += at_chr;
		}
	}

	res->push_back(last_buf);

	return res;
}

const char &nhflib::String::at(usize idx) const {
	if (idx >= length) throw std::out_of_range("String index out of range");
	return stringData[idx];
}


bool char_is_whitespace(char ch) {
	return ch == '\r' || ch == '\n' || ch == ' ';
}

String nhflib::String::trim() const {
	String res;
	usize begin_idx = 0;
	usize end_idx = 0;

	for (usize ii = 0; ii < this->len(); ii++) {
		auto at_chr = this->at(ii);
		if (!char_is_whitespace(at_chr)) {
			begin_idx = ii;
			break;
		}
	}

	for (usize ii = this->len() - 1;; ii--) {
		auto at_chr = this->at(ii);
		if (!char_is_whitespace(at_chr)) {
			end_idx = ii;
			break;
		}

		if (ii == 0) {
			break;
		}
	}

	for (usize ii = begin_idx; ii <= end_idx; ii++) {
		auto at_chr = this->at(ii);
		res += at_chr;
	}

	return res;
}

std::ostream &operator<<(std::ostream &os, const String &s0) {
	os << s0.c_str();
	return os;
}

std::istream &operator>>(std::istream &is, String &s0) {
	// TODO Fix clang shit code that came from iit
	unsigned char ch;
	s0 = String("");
	std::ios_base::fmtflags fl = is.flags();
	is.setf(ios_base::skipws);
	while (is >> ch) {
		is.unsetf(ios_base::skipws);
		if (isspace(ch)) {
			is.putback(ch);
			break;
		} else {
			s0 = s0 + ch;
		}
	}
	is.setf(fl);
	return is;
}

