#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/index-of-from-type-list.hpp>
#include <ncxx/type-list/type-list.hpp>

namespace NOS {

using TestTypeList = TypeList<bool, u8_t, u16_t>;

static_assert(IndexOfFromTypeListV<bool, TestTypeList> == 0);
static_assert(IndexOfFromTypeListV<u8_t, TestTypeList> == 1);
static_assert(IndexOfFromTypeListV<u16_t, TestTypeList> == 2);

} // namespace NOS
