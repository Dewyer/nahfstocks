
#include "RandomProvider.h"
#include <time.h>

void nhflib::RandomProvider::initialize(u32 *seed) {
    if (seed == nullptr) {
        srand(time(nullptr));
    } else {
        srand(*seed);
    }
}
