#include <ncxx/type-trait/add-lvalue-reference.hpp>
#include <ncxx/type-trait/is-same.hpp>

namespace NOS {

static_assert(IsSameV<AddLValueReferenceT<int>, int&>);
static_assert(IsSameV<AddLValueReferenceT<int&>, int&>);

static_assert(IsSameV<AddLValueReferenceT<float>, float&>);
static_assert(IsSameV<AddLValueReferenceT<float&>, float&>);

} // namespace NOS
