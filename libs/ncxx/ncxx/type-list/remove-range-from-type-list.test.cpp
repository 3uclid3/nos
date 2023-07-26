#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/remove-range-from-type-list.hpp>
#include <ncxx/type-list/type-list.hpp>
#include <ncxx/type-trait/is-same.hpp>

namespace NOS {

using TestTypeList = TypeList<u8_t, u16_t, u32_t, u64_t>;
using ExpectedTypeList = TypeList<u8_t, u64_t>;

static_assert(IsSameV<ExpectedTypeList, RemoveRangeFromTypeListT<1, 2, TestTypeList>>);

} // namespace NOS
