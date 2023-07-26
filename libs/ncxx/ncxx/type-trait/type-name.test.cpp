#include <ncxx/type-trait/type-name.hpp>

namespace NOS {
namespace Details {

struct TestType
{
};

using AliasTestType = TestType;

} // namespace Details

// static_assert(TypeNameV<bool> == "bool");

// static_assert(TypeNameV<Details::TestType> == "TestType");
// static_assert(TypeNameV<Details::AliasTestType> == "TestType");

} // namespace NOS
