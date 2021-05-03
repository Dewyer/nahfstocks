#include "./Config.h"

namespace config {
	String Config::COMPANY_COUNT_KEY = "COMPANY_COUNT";
	String Config::TRADER_COUNT_KEY = "TRADER_COUNT";

	void Config::process_config_string_read(const String &line)  {
		auto line_tokens = line.split('=');
		if (line_tokens->size() != 2) {
			throw std::runtime_error("Config key value pair is malformed!");
		}

		auto key = line_tokens->at(0);
		auto val = line_tokens->at(1);

		auto key_def = this->definitions.find([&key](Rc<ConfigKeyDefinition> def) {
			return def->key == *key;
		});

		if (!key_def) {
			std::cout << "Invalid config key given, ignoring";
			return;
		}

		auto config_val = ConfigValue(key_def->type, *val);
		this->configs.insert(*key, config_val);
	}

	void Config::read_from_cin() {
		while (true) {
			auto inp_str_opt = CliHelper::read_safe<String>();
			if (!inp_str_opt) {
				break;
			}

			auto inp_str = inp_str_opt.unwrap();
			if (inp_str == "") {
				break;
			}

			this->process_config_string_read(inp_str);
		}
	}
}