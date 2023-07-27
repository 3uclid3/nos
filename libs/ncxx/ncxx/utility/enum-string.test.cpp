#include <ncxx/utility/enum-string.hpp>

namespace NOS {

enum class SequentialEnum
{
    Value0,
    Value1,
    Value2,

    _Count_
};

constexpr EnumString<SequentialEnum, SequentialEnum::_Count_> SequentialEnumString;

static_assert(SequentialEnumString.string(SequentialEnum::Value0) == "Value0");
static_assert(SequentialEnumString.string(SequentialEnum::Value1) == "Value1");
static_assert(SequentialEnumString.string(SequentialEnum::Value2) == "Value2");

static_assert(SequentialEnumString.value("Value0") == SequentialEnum::Value0);
static_assert(SequentialEnumString.value("Value1") == SequentialEnum::Value1);
static_assert(SequentialEnumString.value("Value2") == SequentialEnum::Value2);

} // namespace NOS
