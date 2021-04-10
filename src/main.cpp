#include <iostream>
#include "../tests/Tests.h"
#include "./simulation/Simulation.h"

int real_main() {
	simulation::Simulation sim;
	std::cout << "End, World!" << std::endl;
	return 0;
}

int test_main() {
	Tests::run_all();
	return 0;
}

int main() {
#ifdef ETEST
	return test_main();
#else
	return real_main();
#endif
}
