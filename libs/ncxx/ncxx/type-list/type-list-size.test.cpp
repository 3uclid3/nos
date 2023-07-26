#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/type-list-size.hpp>
#include <ncxx/type-list/type-list.hpp>

namespace NOS {

static_assert(TypeListSizeV<TypeList<>> == 0);
static_assert(TypeListSizeV<TypeList<bool>> == 1);
static_assert(TypeListSizeV<TypeList<bool, u8_t>> == 2);

} // namespace NOS
