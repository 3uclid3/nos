#include <ncxx/type-trait/add-rvalue-reference.hpp>
#include <ncxx/type-trait/is-same.hpp>

namespace NOS {

static_assert(IsSameV<AddRValueReferenceT<int>, int&&>);
static_assert(IsSameV<AddRValueReferenceT<int&&>, int&&>);

static_assert(IsSameV<AddRValueReferenceT<float>, float&&>);
static_assert(IsSameV<AddRValueReferenceT<float&&>, float&&>);

} // namespace NOS
