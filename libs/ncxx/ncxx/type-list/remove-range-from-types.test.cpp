#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/remove-range-from-type-list.hpp>
#include <ncxx/type-list/type-list.hpp>
#include <ncxx/type-trait/is-same.hpp>

namespace NOS {

using ExpectedTypeList = TypeList<u8_t, u64_t>;

static_assert(IsSameV<ExpectedTypeList, RemoveRangeFromTypesT<1, 2, u8_t, u16_t, u32_t, u64_t>>);

} // namespace NOS
