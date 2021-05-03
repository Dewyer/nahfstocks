#pragma once

#include "../../lib/types.h"
#include "../../lib/option/Option.h"
#include "../../lib/string/String.h"
#include "../../lib/collections/Map.h"
#include "../../lib/collections/Vector.h"
#include "./ConfigValue.h"
#include "../cli/CliHelper.h"

using cli::CliHelper;
using nhflib::Option;
using nhflib::Map;
using nhflib::Vector;
using nhflib::String;

namespace config {

	struct ConfigKeyDefinition {
		String key;
		ConfigValueType type;
	};

	class Config {
	private:
		Map<String, ConfigValue> configs;
		Vector<ConfigKeyDefinition> definitions;

		static String COMPANY_COUNT_KEY;
		static String TRADER_COUNT_KEY;

		void process_config_string_read(const String &line);

		template<typename TVal>
		TVal get_config_with_default(const String &key, TVal default_val) {
			if (!this->configs.has(key)) {
				return default_val;
			}

			auto config_val = this->configs.get(key).unwrap();
			return config_val->template get_val_into<TVal>();
		}

	public:

		Config() {
			this->definitions = Vector<ConfigKeyDefinition>();
			this->configs = Map<String, ConfigValue>();

			this->definitions.push_back(ConfigKeyDefinition{
					Config::COMPANY_COUNT_KEY,
					ConfigValueType::Int
			});
			this->definitions.push_back(ConfigKeyDefinition{
					Config::TRADER_COUNT_KEY,
					ConfigValueType::Int
			});
		}

		virtual void read_from_cin();

		virtual usize get_company_count() {
			auto comp_count = this->get_config_with_default<int>(Config::COMPANY_COUNT_KEY, 40);
			return comp_count;
		}

		virtual usize get_trader_count() {
			auto trader_count = this->get_config_with_default<int>(Config::TRADER_COUNT_KEY, 40);
			return trader_count;
		}

		virtual usize get_fixed_income_interval() const noexcept {
			return 24 * 30;
		}

		virtual usize get_median_starting_cash() const noexcept {
			return 10000;
		}

		virtual usize get_mean_company_outstanding_shares() const noexcept {
			return 1200000;
		}

		virtual f64 get_global_event_chance() const noexcept {
			return 0.01;
		}

		virtual f64 get_sector_event_chance() const noexcept {
			return 0.01;
		}

		virtual f64 get_company_event_chance() const noexcept {
			return 0.01;
		}

		virtual bool should_log() const noexcept {
			return true;
		}

		virtual ~Config() {}

	};
}