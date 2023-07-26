#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/filter-type-list.hpp>
#include <ncxx/type-list/type-list.hpp>
#include <ncxx/type-trait/is-integral.hpp>
#include <ncxx/type-trait/is-same.hpp>

namespace NOS {

using TestTypeList = TypeList<s32_t, u32_t, f32_t, f64_t>;

using FilteredTypes = FilterTypeListT<IsIntegral, TestTypeList>;
using ExpectedTypes = TypeList<s32_t, u32_t>;

static_assert(IsSameV<FilteredTypes, ExpectedTypes>);

} // namespace NOS
