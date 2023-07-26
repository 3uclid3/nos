#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/type-list-contains.hpp>
#include <ncxx/type-list/type-list.hpp>

namespace NOS {

static_assert(!TypeListContainsV<bool, TypeList<>>);
static_assert(TypeListContainsV<bool, TypeList<bool>>);
static_assert(TypeListContainsV<u8_t, TypeList<bool, u8_t, u16_t>>);
static_assert(!TypeListContainsV<u32_t, TypeList<bool, u8_t, u16_t>>);

} // namespace NOS
