#include <base-types.hpp>
#include <type-traits/is-same.hpp>

namespace N {

static_assert(IsSameV<u8_t, u8_t>);

static_assert(!IsSameV<u8_t, u16_t>);
static_assert(!IsSameV<u16_t, u8_t>);

} // namespace N
