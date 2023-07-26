#include <ncxx/type-trait/type-enum-value-name.hpp>

enum class TestEnumClass
{
    ValueA,
    ValueB
};

enum TestEnum
{
    ValueA,
    ValueB
};

static_assert(NOS::TypeEnumValueNameV<TestEnumClass, TestEnumClass::ValueA> == "ValueA");
static_assert(NOS::TypeEnumValueNameV<TestEnumClass, TestEnumClass::ValueB> == "ValueB");

static_assert(NOS::TypeEnumValueNameV<TestEnum, TestEnum::ValueA> == "ValueA");
static_assert(NOS::TypeEnumValueNameV<TestEnum, ValueB> == "ValueB");

namespace NOS {

enum class TestEnumClass
{
    ValueA,
    ValueB
};

enum TestEnum
{
    ValueA,
    ValueB
};

static_assert(TypeEnumValueNameV<TestEnumClass, TestEnumClass::ValueA> == "ValueA");
static_assert(TypeEnumValueNameV<TestEnumClass, TestEnumClass::ValueB> == "ValueB");

static_assert(TypeEnumValueNameV<TestEnum, TestEnum::ValueA> == "ValueA");
static_assert(TypeEnumValueNameV<TestEnum, ValueB> == "ValueB");

} // namespace NOS
