#include <ncxx/basic-types.hpp>
#include <ncxx/container/array.hpp>
#include <ncxx/type-trait/is-array.hpp>

namespace NOS {

static_assert(IsArrayV<Array<u32_t>>);
static_assert(IsArrayV<Array<s32_t>>);

static_assert(!IsArrayV<u32_t>);
static_assert(!IsArrayV<s32_t>);

} // namespace NOS
