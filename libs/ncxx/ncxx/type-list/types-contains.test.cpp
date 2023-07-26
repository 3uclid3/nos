#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/types-contains.hpp>

namespace NOS {

static_assert(!TypesContainsV<bool>);
static_assert(TypesContainsV<bool, bool>);
static_assert(TypesContainsV<u8_t, bool, u8_t, u16_t>);
static_assert(!TypesContainsV<u32_t, bool, u8_t, u16_t>);

} // namespace NOS
