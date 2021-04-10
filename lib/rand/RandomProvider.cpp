
#include "RandomProvider.h"
#include <random>
#include <math.h>

nhflib::RandomProvider::RandomProvider(nhflib::Option<usize> seed) {
	this->seed(std::move(seed));
}

usize nhflib::RandomProvider::next_usize(usize min, usize max) {
	std::uniform_int_distribution<usize> dist(min, max);

	return dist(this->engine);
}

usize nhflib::RandomProvider::next_usize_normal(usize min, usize max, f64 mean, f64 devi) {
	f64 normal = this->next_f64_normal(0, 1, mean, devi);
	return (max - min) * normal + min;
}

f64 nhflib::RandomProvider::next_f64(f64 min, f64 max) {
	std::uniform_real_distribution<f64> dist(min, max);

	return dist(this->engine);
}

f64 nhflib::RandomProvider::next_f64_normal(f64 min, f64 max, f64 mean, f64 devi) {
	f64 xx = this->next_f64(0, 1);
	f64 l_side = 1 / (devi * std::sqrt(2 * nhflib::constants::PI())) * nhflib::constants::E();
	f64 pow_val = -0.5 * std::pow((xx - mean) / devi, 2);
	f64 normal = std::pow(l_side, pow_val);
	return (max - min) * normal + min;
}

void nhflib::RandomProvider::seed(nhflib::Option<usize> seed) {
	if (seed.is_some()) {
		this->engine.seed(seed.unwrap());
	} else {
		std::random_device rd;
		this->engine.seed(rd());
	}
}
