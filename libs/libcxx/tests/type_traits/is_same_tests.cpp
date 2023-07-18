#include <base_types.hpp>
#include <type_traits/is_same.hpp>

namespace nos {

static_assert(is_same_v<u8_t, u8_t>);

static_assert(!is_same_v<u8_t, u16_t>);
static_assert(!is_same_v<u16_t, u8_t>);

} // namespace nos
