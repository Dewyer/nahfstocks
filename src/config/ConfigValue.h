#pragma once
#include "../../lib/string/String.h"

using nhflib::String;

namespace config {

	enum ConfigValueType {
		Int,
		Bool,
	};

	class ConfigValue {
	private:
		String value;
		ConfigValueType type;

		void check_can_parse_string_into_expected_type() const;
	public:
		ConfigValue(const ConfigValueType& expected_type, const String& val) {
			this->type = expected_type;
			this->value = val;

			this->check_can_parse_string_into_expected_type();
		}

		template<typename TOut>
		TOut get_val_into () const;
	};

}