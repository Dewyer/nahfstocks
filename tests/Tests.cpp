#include "../lib/gtest_lite.h"
#include "Tests.h"

void Tests::sanity_test() {
    TEST(SanityTest, SanityTest)
        {
            EXPECT_EQ(10, 10);
        } END
}

void Tests::run_all() {
    Tests::sanity_test();
}
