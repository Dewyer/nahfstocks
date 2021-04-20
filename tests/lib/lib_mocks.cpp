#include "lib_mocks.h"

Rc<RandomProvider> mock_rng() {
	RandomProvider rng_b(Option<usize>::none());
	return nhflib::make_rc(rng_b);
}