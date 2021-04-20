#pragma once

#include "../../lib/rand/RandomProvider.h"
#include "../../lib/option/Option.h"
#include "../../lib/memory/Rc.h"

using nhflib::RandomProvider;
using nhflib::Rc;
using nhflib::Option;

Rc<RandomProvider> mock_rng();