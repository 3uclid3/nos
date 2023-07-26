#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/index-of-from-types.hpp>

namespace NOS {

static_assert(IndexOfFromTypesV<bool, bool, u8_t, u16_t> == 0);
static_assert(IndexOfFromTypesV<u8_t, bool, u8_t, u16_t> == 1);
static_assert(IndexOfFromTypesV<u16_t, bool, u8_t, u16_t> == 2);

} // namespace NOS
