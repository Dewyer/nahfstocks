#include <iostream>
#include "../tests/Tests.h"
#include "cli/SimulationCli.h"
#include "../lib/option/Option.h"

int real_main() {
	cli::SimulationCli sim;
	sim.start();

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
