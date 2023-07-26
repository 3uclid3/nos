#include <ncxx/type-list/for-each-type-list.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/type-list.hpp>

namespace NOS {

template<typename T>
struct VisitedType
{
    static bool visited;
};

template<typename T>
bool VisitedType<T>::visited = false;

TEST_CASE("ForEachTypeList", "[system][TypeList]")
{
    using TestTypeList = TypeList<bool, u8_t, u16_t>;

    VisitedType<bool>::visited = false;
    VisitedType<u8_t>::visited = false;
    VisitedType<u16_t>::visited = false;

    forEachTypeList<TestTypeList>([](auto tagType) {
        using T = typename decltype(tagType)::Type;

        VisitedType<T>::visited = true;
    });

    CHECK(VisitedType<bool>::visited);
    CHECK(VisitedType<u8_t>::visited);
    CHECK(VisitedType<u16_t>::visited);
}

} // namespace NOS
