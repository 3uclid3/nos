#include <ncxx/type-trait/type-full-name.hpp>

namespace NOS {
namespace Details {

struct TestType
{
};

using AliasTestType = TestType;

} // namespace Details

static_assert(TypeFullNameV<bool> == "bool");

static_assert(TypeFullNameV<Details::TestType> == "NOS::Details::TestType");
static_assert(TypeFullNameV<Details::AliasTestType> == "NOS::Details::TestType");

} // namespace NOS
