#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/enable-if-found-in-type-list.hpp>
#include <ncxx/type-list/type-list.hpp>
#include <ncxx/type-trait/is-same.hpp>

namespace NOS {

static_assert(IsSameV<EnableIfFoundInTypeListT<void, u8_t, TypeList<u8_t, u16_t, u32_t>>, void>);
static_assert(IsSameV<EnableIfFoundInTypeListT<void, u16_t, TypeList<u8_t, u16_t, u32_t>>, void>);
static_assert(IsSameV<EnableIfFoundInTypeListT<void, u32_t, TypeList<u8_t, u16_t, u32_t>>, void>);

} // namespace NOS
