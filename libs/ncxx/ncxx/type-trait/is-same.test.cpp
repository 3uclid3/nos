#include <ncxx/basic-types.hpp>
#include <ncxx/type-trait/is-same.hpp>

namespace NOS {

static_assert(IsSameV<u8_t, u8_t>);

static_assert(!IsSameV<u8_t, u16_t>);
static_assert(!IsSameV<u16_t, u8_t>);

} // namespace NOS
