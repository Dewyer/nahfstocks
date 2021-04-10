#include "lib_tests.h"

#ifdef ETEST

#include <functional>
#include "../../lib/external/gtest_lite.h"
#include "../../lib/option/Option.h"
#include "../../lib/collections/Vector.h"
#include "../../lib/algorithms.h"
#include "../../lib/string/String.h"
#include "../../lib/memory/Rc.h"

using namespace nhflib;

class TestClass {
public:
	usize a;
	usize b;
};

template<typename T>
void working_expect_throw(const std::function<void()> &func) {
    bool caught = false;
    try {
        try {
            func();
        } catch (T &err) {
            caught = true;
        }

        EXPECT_EQ(caught, true);
    } catch (std::exception &err) {
        EXPECT_EQ("other", "Bad throw dude!");
    }
}

void run_lib_tests() {
    TEST(LibTests, Option)
        {
            Option<int> opt;

            working_expect_throw<std::runtime_error>([&opt]() {
                opt.unwrap();
            });

            Option<int> opt_two(10);
            int val = opt_two.unwrap();

            EXPECT_EQ(val, 10);
        }
            END

    TEST(LibTests, Vector)
        {
            Vector<int> vec;
            vec.push_back(10);
            vec.push_back(20);
            EXPECT_EQ(vec.size(), static_cast<usize>(2));
            EXPECT_EQ(vec[0], 10);
        }
            END

    TEST(LibTests, Map)
        {
            Vector<int> vec;
            vec.push_back(10);
            vec.push_back(20);

            auto res = nhflib::algo::map<int, double>(vec, [](int &al) { return al + 1.0; });
            EXPECT_EQ(res[0], 11.0);
        }
            END

    TEST(LibTests, String)
        {
            String s1 = "123";
            s1 += "12345";
            EXPECT_STREQ("12312345",s1.c_str());

            String s2 = 'a';
            EXPECT_STREQ( "a", s2.c_str());
        }
            END

	TEST(LibTests, Rc)
		{
    		TestClass test_c;
    		test_c.a = 10;

			Rc<TestClass> tc_rc = Rc<TestClass>::make_rc(test_c);
			auto tc_two = tc_rc;

			EXPECT_TRUE(tc_rc->a == 10);
			EXPECT_TRUE(tc_two->a == 10);
			tc_two->a = 20;
			EXPECT_TRUE(tc_rc->a == 20);
			EXPECT_TRUE(tc_two->a == 20);
		}
			END
}

#else
void run_lib_tests() {
}
#endif