#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/convert-type-list.hpp>
#include <ncxx/type-list/type-list.hpp>

#include <ncxx/type-trait/is-same.hpp>

namespace NOS {

template<typename... TTypes>
struct TestTypeList
{};

using IntegerTypeList = TypeList<s8_t, u8_t, s16_t, u16_t, s32_t, u32_t>;

using ConvertedTypeList = ConvertTypeListT<IntegerTypeList, TestTypeList>;
using ExpectedTypeList = TestTypeList<s8_t, u8_t, s16_t, u16_t, s32_t, u32_t>;

static_assert(IsSameV<ConvertedTypeList, ExpectedTypeList>);

} // namespace NOS
