#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/enable-if-found-in-types.hpp>
#include <ncxx/type-trait/is-same.hpp>

namespace NOS {

static_assert(IsSameV<EnableIfFoundInTypesT<void, u8_t, u8_t, u16_t, u32_t>, void>);
static_assert(IsSameV<EnableIfFoundInTypesT<void, u16_t, u8_t, u16_t, u32_t>, void>);
static_assert(IsSameV<EnableIfFoundInTypesT<void, u32_t, u8_t, u16_t, u32_t>, void>);

} // namespace NOS
