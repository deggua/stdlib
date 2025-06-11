#pragma once

#include <deggua/types.h>
#include <deggua/macros.h>

/* --- CTZ --- */
// count trailing zero bits (LSB to MSB)

static inline usize ctz_128(u128 x)
{
    u64 lo = x;
    u64 hi = x >> 64;

    usize ctz_lo = lo ? __builtin_ctzll(lo) : 64;
    usize ctz_hi = hi ? __builtin_ctzll(hi) : 64;

    return ctz_lo == 64 ? ctz_hi + ctz_lo : ctz_lo;
}

static inline usize ctz_64(u64 x)
{
    return __builtin_ctzll(x);
}

static inline usize ctz_32(u32 x)
{
    return __builtin_ctz(x);
}

static inline usize ctz_16(u16 x)
{
    return min(16, __builtin_ctz(x));
}

static inline usize ctz_8(u8 x)
{
    return min(8, __builtin_ctz(x));
}

#define ctz(x)         \
_Generic((x),          \
    u8:   ctz_8,       \
    u16:  ctz_16,      \
    u32:  ctz_32,      \
    u64:  ctz_64,      \
    u128: ctz_128)((x))

/* --- CLZ --- */
// count leading zero bits (MSB to LSB)

static inline usize clz_128(u128 x)
{
    u64 lo = x;
    u64 hi = x >> 64;

    usize clz_lo = lo ? __builtin_clzll(lo) : 64;
    usize clz_hi = hi ? __builtin_clzll(hi) : 64;

    return clz_hi == 64 ? clz_hi + clz_lo : clz_hi;
}

static inline usize clz_64(u64 x)
{
    return __builtin_clzll(x);
}

static inline usize clz_32(u32 x)
{
    return __builtin_clz(x);
}

static inline usize clz_16(u16 x)
{
    return min(16, __builtin_clz(x));
}

static inline usize clz_8(u8 x)
{
    return min(8, __builtin_clz(x));
}

#define clz(x)         \
_Generic((x),          \
    u8:   clz_8,       \
    u16:  clz_16,      \
    u32:  clz_32,      \
    u64:  clz_64,      \
    u128: clz_128)((x))

/* --- FFS --- */
// find first set bit (LSB to MSB)
// 0 => undefined

static inline usize ffs_128(u128 x)
{
    u64 lo = x;
    u64 hi = x >> 64;

    usize ffs_lo = __builtin_ffsll(lo) - 1;
    usize ffs_hi = __builtin_ffsll(hi) - 1 + 64;

    return min(ffs_lo, ffs_hi);
}

static inline usize ffs_64(u64 x)
{
    return __builtin_ffsll(x) - 1;
}

static inline usize ffs_32(u32 x)
{
    return __builtin_ffs(x) - 1;
}

static inline usize ffs_16(u16 x)
{
    return __builtin_ffs(x) - 1;
}

static inline usize ffs_8(u8 x)
{
    return __builtin_ffs(x) - 1;
}

#define ffs(x)         \
_Generic((x),          \
    u8:   ffs_8,       \
    u16:  ffs_16,      \
    u32:  ffs_32,      \
    u64:  ffs_64,      \
    u128: ffs_128)((x))

/* --- FLS --- */
// find last set bit (LSB to MSB)
// 0 => undefined

static inline usize fls_128(u128 x)
{
    return 128 - 1 - clz_128(x);
}

static inline usize fls_64(u64 x)
{
    return 64 - 1 - clz_64(x);
}

static inline usize fls_32(u64 x)
{
    return 32 - 1 - __builtin_clz(x);
}

static inline usize fls_16(u16 x)
{
    return 16 - 1 - __builtin_clz(x);
}

static inline usize fls_8(u8 x)
{
    return 8 - 1 - __builtin_clz(x);
}

#define fls(x)         \
_Generic((x),          \
    u8:   fls_8,       \
    u16:  fls_16,      \
    u32:  fls_32,      \
    u64:  fls_64,      \
    u128: fls_128)((x))

/* --- PARITY --- */
// return 1 if odd number of bits set, 0 if even number of bits set

static inline usize parity_128(u128 x)
{
    u64 lo = x;
    u64 hi = x >> 64;

    return __builtin_parityll(lo) ^ __builtin_parityll(hi);
}

static inline usize parity_64(u64 x)
{
    return __builtin_parityll(x);
}

static inline usize parity_32(u32 x)
{
    return __builtin_parity(x);
}

static inline usize parity_16(u16 x)
{
    return __builtin_parity(x);
}

static inline usize parity_8(u8 x)
{
    return __builtin_parity(x);
}

#define parity(x)         \
_Generic((x),             \
    u8:   parity_8,       \
    u16:  parity_16,      \
    u32:  parity_32,      \
    u64:  parity_64,      \
    u128: parity_128)((x))

/* --- POPCNT --- */
// population count (count number of set bits)

static inline usize popcnt_128(u128 x)
{
    u64 lo = x;
    u64 hi = x >> 64;

    return __builtin_popcountll(lo) + __builtin_popcountll(hi);
}

static inline usize popcnt_64(u64 x)
{
    return __builtin_popcountll(x);
}

static inline usize popcnt_32(u32 x)
{
    return __builtin_popcount(x);
}

static inline usize popcnt_16(u16 x)
{
    return __builtin_popcount(x);
}

static inline usize popcnt_8(u8 x)
{
    return __builtin_popcount(x);
}

#define popcnt(x)         \
_Generic((x),             \
    u8:   popcnt_8,       \
    u16:  popcnt_16,      \
    u32:  popcnt_32,      \
    u64:  popcnt_64,      \
    u128: popcnt_128)((x))

/* --- BYTEREVERSE --- */
// reverse the bytes of x

static inline u128 bytereverse_128(u128 x)
{
    u64 lo = x;
    u64 hi = x >> 64;

    lo = __builtin_bswap64(lo);
    hi = __builtin_bswap64(hi);

    return ((u128)lo << 64) | hi;
}

static inline u64 bytereverse_64(u64 x)
{
    return __builtin_bswap64(x);
}

static inline u32 bytereverse_32(u32 x)
{
    return __builtin_bswap32(x);
}

static inline u16 bytereverse_16(u16 x)
{
    return __builtin_bswap16(x);
}

static inline u8 bytereverse_8(u8 x)
{
    return x;
}

#define bytereverse(x)         \
_Generic((x),                  \
    u8:   bytereverse_8,       \
    u16:  bytereverse_16,      \
    u32:  bytereverse_32,      \
    u64:  bytereverse_64,      \
    u128: bytereverse_128)((x))

/* --- BITREVERSE --- */
// reverse the bits of x

static inline u128 bitreverse_128(u128 x)
{
    u64 lo = x;
    u64 hi = x >> 64;

    u64 lo_rev = __builtin_bitreverse64(lo);
    u64 hi_rev = __builtin_bitreverse64(hi);

    return ((u128)lo_rev << 64) | hi;
}

static inline u64 bitreverse_64(u64 x)
{
    return __builtin_bitreverse64(x);
}

static inline u32 bitreverse_32(u32 x)
{
    return __builtin_bitreverse32(x);
}

static inline u16 bitreverse_16(u16 x)
{
    return __builtin_bitreverse16(x);
}

static inline u8 bitreverse_8(u8 x)
{
    return __builtin_bitreverse8(x);
}

#define bitreverse(x)         \
_Generic((x),                 \
    u8:   bitreverse_8,       \
    u16:  bitreverse_16,      \
    u32:  bitreverse_32,      \
    u64:  bitreverse_64,      \
    u128: bitreverse_128)((x))

/* --- ROTR --- */
// rotate x to the right by r bits

static inline u128 rotr_128(u128 x, usize r)
{
    const usize mask = 128 - 1;
    return (x >> (r & mask)) | (x << (-r & mask));
}

static inline u64 rotr_64(u64 x, usize r)
{
    return __builtin_rotateright64(x, r);
}

static inline u32 rotr_32(u32 x, usize r)
{
    return __builtin_rotateright32(x, r);
}

static inline u16 rotr_16(u16 x, usize r)
{
    return __builtin_rotateright16(x, r);
}

static inline u8 rotr_8(u8 x, usize r)
{
    return __builtin_rotateright8(x, r);
}

#define rotr(x, r)           \
_Generic((x),                \
    u8:   rotr_8,            \
    u16:  rotr_16,           \
    u32:  rotr_32,           \
    u64:  rotr_64,           \
    u128: rotr_128)((x), (r))

/* --- ROTL --- */
// rotate x to the left by r bits

static inline u128 rotl_128(u128 x, usize r)
{
    const usize mask = 128 - 1;
    return (x << (r & mask)) | (x >> (-r & mask));
}

static inline u64 rotl_64(u64 x, usize r)
{
    return __builtin_rotateleft64(x, r);
}

static inline u32 rotl_32(u32 x, usize r)
{
    return __builtin_rotateleft32(x, r);
}

static inline u16 rotl_16(u16 x, usize r)
{
    return __builtin_rotateleft16(x, r);
}

static inline u8 rotl_8(u8 x, usize r)
{
    return __builtin_rotateleft8(x, r);
}

#define rotl(x, r)           \
_Generic((x),                \
    u8:   rotl_8,            \
    u16:  rotl_16,           \
    u32:  rotl_32,           \
    u64:  rotl_64,           \
    u128: rotl_128)((x), (r))

/* --- ISPOW2 --- */
// determine if integer is power of 2

static inline bool ispow2_128(u128 x)
{
    return !!(x & ((x & (x - 1)) == 0));
}

static inline bool ispow2_64(u64 x)
{
    return !!(x & ((x & (x - 1)) == 0));
}

static inline bool ispow2_32(u32 x)
{
    return !!(x & ((x & (x - 1)) == 0));
}

static inline bool ispow2_16(u16 x)
{
    return !!(x & ((x & (x - 1)) == 0));
}

static inline bool ispow2_8(u8 x)
{
    return !!(x & ((x & (x - 1)) == 0));
}

#define ispow2(x)         \
_Generic((x),             \
    u8:   ispow2_8,       \
    u16:  ispow2_16,      \
    u32:  ispow2_32,      \
    u64:  ispow2_64,      \
    u128: ispow2_128)((x))

/* --- ILOG2 --- */
// integer log2 (rounded down)

static inline usize ilog2_128(u128 x)
{
    return 128 - clz_128(x) - 1;
}

static inline usize ilog2_64(u64 x)
{
    return 64 - clz_64(x) - 1;
}

static inline usize ilog2_32(u32 x)
{
    return 32 - clz_32(x) - 1;
}

static inline usize ilog2_16(u16 x)
{
    return 16 - clz_16(x) - 1;
}

static inline usize ilog2_8(u8 x)
{
    return 8 - clz_8(x) - 1;
}

#define ilog2(x)         \
_Generic((x),            \
    u8:   ilog2_8,       \
    u16:  ilog2_16,      \
    u32:  ilog2_32,      \
    u64:  ilog2_64,      \
    u128: ilog2_128)((x))

/* --- BITWIDTH --- */
// minimum number of bits to represent x (0b0 => 1 bit, 0b10 => 2 bits, ...)

static inline usize bitwidth_128(u128 x)
{
    return x ? ilog2_128(x) + 1 : 1;
}

static inline usize bitwidth_64(u64 x)
{
    return x ? ilog2_64(x) + 1 : 1;
}

static inline usize bitwidth_32(u32 x)
{
    return x ? ilog2_32(x) + 1 : 1;
}

static inline usize bitwidth_16(u16 x)
{
    return x ? ilog2_16(x) + 1 : 1;
}

static inline usize bitwidth_8(u8 x)
{
    return x ? ilog2_8(x) + 1 : 1;
}

#define bitwidth(x)         \
_Generic((x),               \
    u8:   bitwidth_8,       \
    u16:  bitwidth_16,      \
    u32:  bitwidth_32,      \
    u64:  bitwidth_64,      \
    u128: bitwidth_128)((x))

/* --- ALIGNP2 --- */
// round x up to a multiple of a power of 2

static inline u128 alignp2_128(u128 x, u128 align_pow2)
{
    return -(-x & -align_pow2);
}

static inline u64 alignp2_64(u64 x, u64 align_pow2)
{
    return -(-x & -align_pow2);
}

static inline u32 alignp2_32(u32 x, u32 align_pow2)
{
    return -(-x & -align_pow2);
}

static inline u16 alignp2_16(u16 x, u16 align_pow2)
{
    return -(-x & -align_pow2);
}

static inline u8 alignp2_8(u8 x, u8 align_pow2)
{
    return -(-x & -align_pow2);
}

#define alignp2(x, align_pow2)           \
_Generic((x),                           \
    u8:   alignp2_8,                     \
    u16:  alignp2_16,                    \
    u32:  alignp2_32,                    \
    u64:  alignp2_64,                    \
    u128: alignp2_128)((x), (align_pow2))

/* --- FLOORP2 --- */
// floor pow 2 (next pow2 <= x)

static inline u128 floorp2_128(u128 x)
{
    return U128_C(1) << (128 - 1 - clz_128(x));
}

static inline u64 floorp2_64(u64 x)
{
    return U64_C(1) << (64 - 1 - clz_64(x));
}

static inline u32 floorp2_32(u32 x)
{
    return U32_C(1) << (32 - 1 - clz_32(x));
}

static inline u16 floorp2_16(u16 x)
{
    return U16_C(1) << (16 - 1 - clz_16(x));
}

static inline u8 floorp2_8(u8 x)
{
    return U8_C(1) << (8 - 1 - clz_8(x));
}

#define floorp2(x)         \
_Generic((x),              \
    u8:   floorp2_8,       \
    u16:  floorp2_16,      \
    u32:  floorp2_32,      \
    u64:  floorp2_64,      \
    u128: floorp2_128)((x))

/* --- CEILP2 --- */
// ceil pow 2 (next pow2 >= x)

static inline u128 ceilp2_128(u128 x)
{
    return U128_C(1) << (128 - clz_128(x - 1));
}

static inline u64 ceilp2_64(u64 x)
{
    return U64_C(1) << (64 - clz_64(x - 1));
}

static inline u32 ceilp2_32(u32 x)
{
    return U32_C(1) << (32 - clz_32(x - 1));
}

static inline u16 ceilp2_16(u16 x)
{
    return U16_C(1) << (16 - clz_16(x - 1));
}

static inline u8 ceilp2_8(u8 x)
{
    return U8_C(1) << (8 - clz_8(x - 1));
}

#define ceilp2(x)         \
_Generic((x),             \
    u8:   ceilp2_8,       \
    u16:  ceilp2_16,      \
    u32:  ceilp2_32,      \
    u64:  ceilp2_64,      \
    u128: ceilp2_128)((x))
