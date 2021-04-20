#pragma once

#include "../../lib/memory/Rc.h"
#include "../../src/config/Config.h"

using nhflib::Rc;

Rc<config::Config> mock_config();