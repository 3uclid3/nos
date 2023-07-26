#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/type-at-from-type-list.hpp>
#include <ncxx/type-list/type-list.hpp>
#include <ncxx/type-trait/is-same.hpp>

namespace NOS {

using TestTypeList = TypeList<bool, u8_t, u16_t>;

static_assert(IsSameV<TypeAtFromTypeListT<0, TestTypeList>, bool>);
static_assert(IsSameV<TypeAtFromTypeListT<1, TestTypeList>, u8_t>);
static_assert(IsSameV<TypeAtFromTypeListT<2, TestTypeList>, u16_t>);

} // namespace NOS
