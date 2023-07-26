#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/type-at-from-types.hpp>
#include <ncxx/type-trait/is-same.hpp>

namespace NOS {

static_assert(IsSameV<TypeAtFromTypesT<0, bool, u8_t, u16_t>, bool>);
static_assert(IsSameV<TypeAtFromTypesT<1, bool, u8_t, u16_t>, u8_t>);
static_assert(IsSameV<TypeAtFromTypesT<2, bool, u8_t, u16_t>, u16_t>);

} // namespace NOS
