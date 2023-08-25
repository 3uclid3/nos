#include <ncxx/test/object.fake.hpp>
#include <ncxx/type-trait/is-copy-constructible.hpp>

namespace NOS {

static_assert(IsCopyConstructibleV<Fake::Object>);

} // namespace NOS
