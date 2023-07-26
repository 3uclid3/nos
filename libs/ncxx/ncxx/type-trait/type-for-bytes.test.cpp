#include <ncxx/type-trait/is-same.hpp>
#include <ncxx/type-trait/type-for-bytes.hpp>

namespace NOS {

static_assert(IsSameV<TypeForBytesT<1, Signed::Yes>, s8_t>);
static_assert(IsSameV<TypeForBytesT<2, Signed::Yes>, s16_t>);
static_assert(IsSameV<TypeForBytesT<4, Signed::Yes>, s32_t>);
static_assert(IsSameV<TypeForBytesT<8, Signed::Yes>, s64_t>);

static_assert(IsSameV<TypeForBytesT<1, Signed::No>, u8_t>);
static_assert(IsSameV<TypeForBytesT<2, Signed::No>, u16_t>);
static_assert(IsSameV<TypeForBytesT<4, Signed::No>, u32_t>);
static_assert(IsSameV<TypeForBytesT<8, Signed::No>, u64_t>);

} // namespace NOS
