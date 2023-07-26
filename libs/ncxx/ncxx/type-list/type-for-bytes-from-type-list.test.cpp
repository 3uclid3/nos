#include <ncxx/type-list/type-for-bytes-from-type-list.hpp>
#include <ncxx/type-list/type-list.hpp>

#include <ncxx/type-trait/is-same.hpp>

namespace NOS {

static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<u8_t>, Signed::No>, u8_t>);
static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<u16_t>, Signed::No>, u16_t>);
static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<u32_t>, Signed::No>, u32_t>);
static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<u64_t>, Signed::No>, u64_t>);
static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<s8_t>, Signed::No>, u8_t>);
static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<s16_t>, Signed::No>, u16_t>);
static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<s32_t>, Signed::No>, u32_t>);
static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<s64_t>, Signed::No>, u64_t>);

static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<u8_t, s8_t>, Signed::No>, u16_t>);
static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<u8_t, s8_t, u8_t>, Signed::No>, u32_t>);
static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<u8_t, s8_t, u8_t, s8_t>, Signed::No>, u32_t>);

static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<u8_t>, Signed::Yes>, s8_t>);
static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<u16_t>, Signed::Yes>, s16_t>);
static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<u32_t>, Signed::Yes>, s32_t>);
static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<u64_t>, Signed::Yes>, s64_t>);
static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<s8_t>, Signed::Yes>, s8_t>);
static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<s16_t>, Signed::Yes>, s16_t>);
static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<s32_t>, Signed::Yes>, s32_t>);
static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<s64_t>, Signed::Yes>, s64_t>);

static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<u8_t, s8_t>, Signed::Yes>, s16_t>);
static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<u8_t, s8_t, u8_t>, Signed::Yes>, s32_t>);
static_assert(IsSameV<TypeForBytesFromTypeListT<TypeList<u8_t, s8_t, u8_t, s8_t>, Signed::Yes>, s32_t>);

} // namespace NOS
