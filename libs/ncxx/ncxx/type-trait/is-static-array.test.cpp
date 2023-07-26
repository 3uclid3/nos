#include <ncxx/basic-types.hpp>
#include <ncxx/container/static-array.hpp>
#include <ncxx/type-trait/is-static-array.hpp>

namespace NOS {

static_assert(IsStaticArrayV<StaticArray<u32_t, 32>>);
static_assert(IsStaticArrayV<StaticArray<s32_t, 32>>);

static_assert(!IsStaticArrayV<u32_t>);
static_assert(!IsStaticArrayV<s32_t>);

} // namespace NOS
