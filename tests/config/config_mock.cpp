#include "config_mock.h"

class MockConfig : public config::Config {
	bool should_log() const noexcept override {
		return false;
	}
};

Rc<config::Config> mock_config() {
	return nhflib::make_rc(new MockConfig()).base_rc<config::Config>();
}
