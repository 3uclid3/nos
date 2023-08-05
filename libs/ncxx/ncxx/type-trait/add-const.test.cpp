#include <ncxx/type-trait/add-const.hpp>
#include <ncxx/type-trait/is-same.hpp>

namespace NOS {

static_assert(IsSameV<AddConstT<int>, const int>);
static_assert(IsSameV<AddConstT<float>, const float>);

} // namespace NOS
