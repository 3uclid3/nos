#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/transform-type-list.hpp>
#include <ncxx/type-list/type-list.hpp>
#include <ncxx/type-trait/is-same.hpp>

namespace NOS {

template<typename T>
struct Decorator
{
};

template<typename T>
struct Transform
{
    using Type = Decorator<T>;
};

using TestTypeList = TypeList<bool, u8_t, u16_t>;

using TransformedTypeList = TransformTypeListT<Transform, TestTypeList>;
using ExpectedTypeList = TypeList<Decorator<bool>, Decorator<u8_t>, Decorator<u16_t>>;

static_assert(IsSameV<TransformedTypeList, ExpectedTypeList>);

} // namespace NOS
