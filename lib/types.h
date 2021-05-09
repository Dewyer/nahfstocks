#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <cmath>

typedef std::size_t usize;
typedef unsigned int u32;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;
typedef long double f128;

namespace nhflib {
	namespace constants {
		constexpr double PI() { return 3.14159265358979323846; }

		constexpr double E() { return 2.718281828459045235360; }
	}
}

