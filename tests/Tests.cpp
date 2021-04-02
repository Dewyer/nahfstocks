#ifdef ETEST

#include "../lib/external/gtest_lite.h"
#include "./lib/libtests.h"

#include "Tests.h"

void Tests::sanity_test() {
    TEST(SanityTest, SanityTest)
        {
            EXPECT_EQ(10, 10);
        }
            END
}

void Tests::run_all() {
    Tests::sanity_test();
    run_lib_tests();
}

#else
#include "Tests.h"

void Tests::sanity_test() {
}

void Tests::run_all() {
}
#endif