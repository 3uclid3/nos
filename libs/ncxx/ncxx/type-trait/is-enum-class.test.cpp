#include <ncxx/basic-types.hpp>
#include <ncxx/type-trait/is-enum-class.hpp>

namespace NOS {

enum class EnumClassA { V0 };
enum class EnumClassB { V1 };

enum EnumNonClassA { EnumNonClassA_V0 };
enum EnumNonClassB { EnumNonClassB_V1 };

static_assert(IsEnumClassV<EnumClassA>);
static_assert(IsEnumClassV<EnumClassB>);

static_assert(!IsEnumClassV<EnumNonClassA>);
static_assert(!IsEnumClassV<EnumNonClassB>);

static_assert(!IsEnumClassV<u32_t>);
static_assert(!IsEnumClassV<s32_t>);

} // namespace NOS
