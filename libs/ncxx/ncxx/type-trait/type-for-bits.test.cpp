#include <ncxx/type-trait/is-same.hpp>
#include <ncxx/type-trait/type-for-bits.hpp>

namespace NOS {

static_assert(IsSameV<TypeForBitsT<1, Signed::Yes>, s8_t>);
static_assert(IsSameV<TypeForBitsT<8, Signed::Yes>, s8_t>);

static_assert(IsSameV<TypeForBitsT<9, Signed::Yes>, s16_t>);
static_assert(IsSameV<TypeForBitsT<16, Signed::Yes>, s16_t>);

static_assert(IsSameV<TypeForBitsT<17, Signed::Yes>, s32_t>);
static_assert(IsSameV<TypeForBitsT<32, Signed::Yes>, s32_t>);

static_assert(IsSameV<TypeForBitsT<33, Signed::Yes>, s64_t>);
static_assert(IsSameV<TypeForBitsT<64, Signed::Yes>, s64_t>);

static_assert(IsSameV<TypeForBitsT<1, Signed::No>, u8_t>);
static_assert(IsSameV<TypeForBitsT<8, Signed::No>, u8_t>);

static_assert(IsSameV<TypeForBitsT<9, Signed::No>, u16_t>);
static_assert(IsSameV<TypeForBitsT<16, Signed::No>, u16_t>);

static_assert(IsSameV<TypeForBitsT<17, Signed::No>, u32_t>);
static_assert(IsSameV<TypeForBitsT<32, Signed::No>, u32_t>);

static_assert(IsSameV<TypeForBitsT<33, Signed::No>, u64_t>);
static_assert(IsSameV<TypeForBitsT<64, Signed::No>, u64_t>);

} // namespace NOS
