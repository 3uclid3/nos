#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/concatenate-type-lists.hpp>
#include <ncxx/type-list/type-list.hpp>

#include <ncxx/type-trait/is-same.hpp>

namespace NOS {

using TestTypeListS = TypeList<s32_t, s64_t>;
using TestTypeListU = TypeList<u32_t, u64_t>;

using ConcatenatedTypeList = ConcatenateTypeListsT<TestTypeListS, TestTypeListU>;
using ExpectedTypeList = TypeList<s32_t, s64_t, u32_t, u64_t>;

static_assert(IsSameV<ConcatenatedTypeList, ExpectedTypeList>);

} // namespace NOS
