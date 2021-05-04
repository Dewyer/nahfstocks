//
// Created by Barna on 2021. 05. 03..
//

#include "ConfigValue.h"

namespace config {
	template<>
	int ConfigValue::get_val_into<int>() const {
		if (this->type != ConfigValueType::Int) {
			throw std::runtime_error("Config value is not int.");
		}

		try {
			return std::stoi(this->value.c_str());
		} catch (...) {
			throw std::runtime_error("Config value of type in cannot be parsed from given value.");
		}
	}

	template<>
	bool ConfigValue::get_val_into<bool>() const {
		if (this->type != ConfigValueType::Bool) {
			throw std::runtime_error("Config value is not a bool.");
		}

		return this->value == "true" || this->value == "True" || this->value == "1";
	}

	void ConfigValue::check_can_parse_string_into_expected_type() const {
		switch (this->type) {
			case ConfigValueType::Int:
				this->get_val_into<int>();
				break;
			case ConfigValueType::Bool:
				this->get_val_into<bool>();
				break;
			default:
				return;
		}
	}
}