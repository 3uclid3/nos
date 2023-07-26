#include <catch2/catch_test_macros.hpp>

#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/for-each-types.hpp>

namespace NOS {

template<typename T>
struct VisitedType
{
    static bool visited;
};

template<typename T>
bool VisitedType<T>::visited = false;

TEST_CASE("forEachTypes", "[system][TypeList]")
{
    VisitedType<bool>::visited = false;
    VisitedType<u8_t>::visited = false;
    VisitedType<u16_t>::visited = false;

    forEachTypes<bool, u8_t, u16_t>([](auto tagType) {
        using T = typename decltype(tagType)::Type;

        VisitedType<T>::visited = true; });

    CHECK(VisitedType<bool>::visited);
    CHECK(VisitedType<u8_t>::visited);
    CHECK(VisitedType<u16_t>::visited);
}

} // namespace NOS
