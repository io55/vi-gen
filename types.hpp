#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef std::int8_t s8;
typedef std::int16_t s16;
typedef std::int32_t s32;
typedef std::int64_t s64;

typedef std::uint8_t u8;
typedef std::uint16_t u16;
typedef std::uint32_t u32;
typedef std::uint64_t u64;

typedef float f32;
typedef double f64;

namespace math {
constexpr f64 gPi  = 3.14159265358979323846;
constexpr f64 gTau = gPi * 2;

// Used for converting Radians to Degrees
constexpr f64 gRad2Deg = 360 / gTau;
constexpr f64 gDeg2Rad = gTau / 360;
} // namespace math

#ifdef __cplusplus
static_assert(sizeof(s8) == 1 && sizeof(u8) == 1, "8 bit number isn't 1 byte");
static_assert(sizeof(s16) == 2 && sizeof(u16) == 2,
              "16 bit number isn't 2 bytes");
static_assert(sizeof(s32) == 4 && sizeof(u32) == 4,
              "32 bit number isn't 4 bytes");
static_assert(sizeof(s64) == 8 && sizeof(u64) == 8,
              "64 bit number isn't 8 bytes");
static_assert(sizeof(f32) == 4, "32 bit floating point number isn't 4 bytes");
static_assert(sizeof(f64) == 8, "64 bit floating point number isn't 8 bytes");
#endif