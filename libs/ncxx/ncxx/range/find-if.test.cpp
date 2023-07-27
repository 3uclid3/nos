#include <ncxx/range/find-if.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/container/static-array.hpp>

namespace NOS::Range {

TEST_CASE("findIf", "[range]")
{
    auto isEven = [](int v) { return (v % 2) == 0; };
    auto isOdd = [](int v) { return (v % 2) != 0; };

    StaticArray values = toStaticArray<int>({0, 2, 4, 6});

    CHECK(findIf(values, isEven) == values.begin());
    CHECK(findIf(values, isOdd) == values.end());
}

} // namespace NOS::Range
