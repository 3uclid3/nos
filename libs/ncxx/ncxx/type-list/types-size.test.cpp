#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/types-size.hpp>

namespace NOS {

static_assert(TypesSizeV<> == 0);
static_assert(TypesSizeV<bool> == 1);
static_assert(TypesSizeV<bool, u8_t> == 2);

} // namespace NOS
