#pragma once

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>

#ifdef _WIN32
#    include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#else
#    include <unistd.h>
#endif

#include <deggua/macros.h>

#define U8_DEC_FMT  "%" PRIu8
#define U16_DEC_FMT "%" PRIu16
#define U32_DEC_FMT "%" PRIu32
#define U64_DEC_FMT "%" PRIu64

#define U8_HEX_FMT "%02" PRIx8

#define U16_HEX_FMT "%04" PRIx16

#define U32_HEX_FMT "%08" PRIx32

#define U64_HEX_FMT "%016" PRIx64

#define U128_HEX_FMT      "%016" PRIx64 "%016" PRIx64
#define U128_HEX_ARG(x) (u64)((x) >> 64), (u64)((x))

#define UPTR_FMT    "%p"
#define UPTR_ARG(x) ((void*)(x))

#define IPTR_FMT    "%p"
#define IPTR_ARG(x) ((void*)(x))

#define I8_DEC_FMT  "%" PRId8
#define I16_DEC_FMT "%" PRId16
#define I32_DEC_FMT "%" PRId32
#define I64_DEC_FMT "%" PRId64

#define I8_HEX_FMT  "%02" PRIx8
#define I16_HEX_FMT "%04" PRIx16
#define I32_HEX_FMT "%08" PRIx32
#define I64_HEX_FMT "%016" PRIx64

#define F32_C(x) ((f32)(x))
#define F64_C(x) ((f64)(x))

#define U8_C(x)   ((u8)(x))
#define U16_C(x)  ((u16)(x))
#define U32_C(x)  ((u32)(x))
#define U64_C(x)  ((u64)(x))
#define U128_C(x) ((u128)(x))

#define I8_C(x)   ((i8)(x))
#define I16_C(x)  ((i16)(x))
#define I32_C(x)  ((i32)(x))
#define I64_C(x)  ((i64)(x))
#define I128_C(x) ((i128)(x))

#define USIZE_C(x) ((usize)(x))
#define ISIZE_C(x) ((isize)(x))

#define U8_MIN   (U8_C(0))
#define U16_MIN  (U16_C(0))
#define U32_MIN  (U32_C(0))
#define U64_MIN  (U64_C(0))
#define U128_MIN (U128_C(0))

#define I8_MIN   (INT8_MIN)
#define I16_MIN  (INT16_MIN)
#define I32_MIN  (INT32_MIN)
#define I64_MIN  (INT64_MIN)
#define I128_MIN ((i128)(U128_C(1) << 127))

#define USIZE_MIN (USIZE_C(0))
#define USIZE_MAX (~USIZE_C(0))

#define ISIZE_MIN ((isize)(USIZE_C(1) << (sizeof(isize) * CHAR_BIT - 1)))
#define ISIZE_MAX ((isize)((USIZE_C(1) << (sizeof(isize) * CHAR_BIT - 1)) - 1))

typedef float  f32;
typedef double f64;

typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef uint64_t    u64;
typedef __uint128_t u128;

typedef int8_t     i8;
typedef int16_t    i16;
typedef int32_t    i32;
typedef int64_t    i64;
typedef __int128_t i128;

typedef uint_fast8_t  u8f;
typedef uint_fast16_t u16f;
typedef uint_fast32_t u32f;
typedef uint_fast64_t u64f;

typedef int_fast8_t  i8f;
typedef int_fast16_t i16f;
typedef int_fast32_t i32f;
typedef int_fast64_t i64f;

typedef uint_least8_t  u8m;
typedef uint_least16_t u16m;
typedef uint_least32_t u32m;
typedef uint_least64_t u64m;

typedef int_least8_t  i8m;
typedef int_least16_t i16m;
typedef int_least32_t i32m;
typedef int_least64_t i64m;

typedef size_t  usize;
typedef ssize_t isize;

typedef uintptr_t uptr;
typedef intptr_t  iptr;

typedef union {
    f32 f32;

    struct {
        u32 frac : 23;
        u32 exp  : 8;
        u32 sign : 1;
    };

    u32 u32;
    u8  u8[sizeof(f32)];
} f32_ieee754;

typedef union {
    f64 f64;

    struct {
        u64 frac : 52;
        u64 exp  : 11;
        u64 sign : 1;
    };

    u64 u64;
    u8  u8[sizeof(f64)];
} f64_ieee754;

STATIC_ASSERT(sizeof(f32) == 4);
STATIC_ASSERT(sizeof(f64) == 8);
STATIC_ASSERT(sizeof(f32_ieee754) == 4);
STATIC_ASSERT(sizeof(f64_ieee754) == 8);
