#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/type-for-bytes-from-types.hpp>
#include <ncxx/type-trait/is-same.hpp>

namespace NOS {

static_assert(IsSameV<TypeForBytesFromTypesT<Signed::No, u8_t>, u8_t>);
static_assert(IsSameV<TypeForBytesFromTypesT<Signed::No, u16_t>, u16_t>);
static_assert(IsSameV<TypeForBytesFromTypesT<Signed::No, u32_t>, u32_t>);
static_assert(IsSameV<TypeForBytesFromTypesT<Signed::No, u64_t>, u64_t>);
static_assert(IsSameV<TypeForBytesFromTypesT<Signed::No, s8_t>, u8_t>);
static_assert(IsSameV<TypeForBytesFromTypesT<Signed::No, s16_t>, u16_t>);
static_assert(IsSameV<TypeForBytesFromTypesT<Signed::No, s32_t>, u32_t>);
static_assert(IsSameV<TypeForBytesFromTypesT<Signed::No, s64_t>, u64_t>);

static_assert(IsSameV<TypeForBytesFromTypesT<Signed::No, u8_t, s8_t>, u16_t>);
static_assert(IsSameV<TypeForBytesFromTypesT<Signed::No, u8_t, s8_t, u8_t>, u32_t>);
static_assert(IsSameV<TypeForBytesFromTypesT<Signed::No, u8_t, s8_t, u8_t, s8_t>, u32_t>);

static_assert(IsSameV<TypeForBytesFromTypesT<Signed::Yes, s8_t>, s8_t>);
static_assert(IsSameV<TypeForBytesFromTypesT<Signed::Yes, s16_t>, s16_t>);
static_assert(IsSameV<TypeForBytesFromTypesT<Signed::Yes, s32_t>, s32_t>);
static_assert(IsSameV<TypeForBytesFromTypesT<Signed::Yes, s64_t>, s64_t>);
static_assert(IsSameV<TypeForBytesFromTypesT<Signed::Yes, u8_t>, s8_t>);
static_assert(IsSameV<TypeForBytesFromTypesT<Signed::Yes, u16_t>, s16_t>);
static_assert(IsSameV<TypeForBytesFromTypesT<Signed::Yes, u32_t>, s32_t>);
static_assert(IsSameV<TypeForBytesFromTypesT<Signed::Yes, u64_t>, s64_t>);

static_assert(IsSameV<TypeForBytesFromTypesT<Signed::Yes, u8_t, s8_t>, s16_t>);
static_assert(IsSameV<TypeForBytesFromTypesT<Signed::Yes, u8_t, s8_t, u8_t>, s32_t>);
static_assert(IsSameV<TypeForBytesFromTypesT<Signed::Yes, u8_t, s8_t, u8_t, s8_t>, s32_t>);

} // namespace NOS
