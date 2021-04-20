#pragma once

#ifdef ETEST
// Conditional compilation test
#define CC_TEST(fn, body) \
fn \
body \

#else

#define CC_TEST(fn, body) \
fn {}

#endif