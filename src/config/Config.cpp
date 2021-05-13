#include <iostream>
#include <fstream>
#include "./Config.h"

namespace config {
	const char *Config::SKIP_CIN_CONFIG_KEY = "SKIP_CIN_CONFIG";
	const char *Config::INTERACTIVE_MODE_KEY = "INTERACTIVE_MODE";
	const char *Config::CYCLE_LIMITS_KEY = "CYCLE_LIMITS";
	const char *Config::SEED_KEY = "SEED";
	const char *Config::LOG_LEVEL_KEY = "LOG_LEVEL";
	const char *Config::EARNINGS_CYCLES_KEY = "EARNINGS_CYCLES";
	const char *Config::DIVIDEND_CYCLES_KEY = "DIVIDEND_CYCLES";
	const char *Config::TRADER_MONEY_KEY = "TRADER_MONEY";
	const char *Config::TRADER_INCOME_KEY = "TRADER_INCOME";
	const char *Config::MEDIAN_IPO_KEY = "MEDIAN_IPO";
	const char *Config::PRICE_SAMPLING_RATE_KEY = "PRICE_SAMPLING_RATE";
	const char *Config::COMPANY_COUNT_KEY = "COMPANY_COUNT";
	const char *Config::TRADER_COUNT_KEY = "TRADER_COUNT";
	const char *Config::DUMP_JSON_KEY = "DUMP_JSON";

	void Config::process_config_string_read(const String &line) {
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

	void Config::read_config_from_cin() {
		this->cumulative_read_config_from_stream(std::cin);
	}

	void Config::create_config_definitions() {
		this->definitions.push_back(ConfigKeyDefinition{
				Config::INTERACTIVE_MODE_KEY,
				ConfigValueType::Bool
		});
		this->definitions.push_back(ConfigKeyDefinition{
				Config::CYCLE_LIMITS_KEY,
				ConfigValueType::Int
		});
		this->definitions.push_back(ConfigKeyDefinition{
				Config::SEED_KEY,
				ConfigValueType::Int
		});
		this->definitions.push_back(ConfigKeyDefinition{
				Config::LOG_LEVEL_KEY,
				ConfigValueType::Int
		});
		this->definitions.push_back(ConfigKeyDefinition{
				Config::EARNINGS_CYCLES_KEY,
				ConfigValueType::Int
		});
		this->definitions.push_back(ConfigKeyDefinition{
				Config::DIVIDEND_CYCLES_KEY,
				ConfigValueType::Int
		});
		this->definitions.push_back(ConfigKeyDefinition{
				Config::TRADER_MONEY_KEY,
				ConfigValueType::Int
		});
		this->definitions.push_back(ConfigKeyDefinition{
				Config::TRADER_INCOME_KEY,
				ConfigValueType::Int
		});
		this->definitions.push_back(ConfigKeyDefinition{
				Config::MEDIAN_IPO_KEY,
				ConfigValueType::Int
		});
		this->definitions.push_back(ConfigKeyDefinition{
				Config::PRICE_SAMPLING_RATE_KEY,
				ConfigValueType::Int
		});
		this->definitions.push_back(ConfigKeyDefinition{
				Config::COMPANY_COUNT_KEY,
				ConfigValueType::Int
		});
		this->definitions.push_back(ConfigKeyDefinition{
				Config::TRADER_COUNT_KEY,
				ConfigValueType::Int
		});
		this->definitions.push_back(ConfigKeyDefinition{
				Config::SKIP_CIN_CONFIG_KEY,
				ConfigValueType::Bool
		});
		this->definitions.push_back(ConfigKeyDefinition{
				Config::DUMP_JSON_KEY,
				ConfigValueType::Bool
		});
	}

	void Config::read_config_from_dot_config() {
		std::ifstream dot_file(".config");
		if (!dot_file.is_open()) {
			return;
		}

		this->cumulative_read_config_from_stream(dot_file);
	}

	void Config::cumulative_read_config_from_stream(std::istream &in) {
		while (true) {
			auto inp_str_opt = CliHelper::read_safe<String>(in);
			if (!inp_str_opt) {
				break;
			}

			auto inp_str = inp_str_opt.unwrap().trim();
			if (inp_str == "" || inp_str == "END") {
				break;
			}

			this->process_config_string_read(inp_str);
		}
	}

	void Config::read_config() {
		this->configs.clear();

		this->read_config_from_dot_config();
		auto skip_cin = this->get_config_with_default(Config::SKIP_CIN_CONFIG_KEY, false);

		if (!skip_cin) {
			this->read_config_from_cin();
		}
	}
}