#include <catch2/catch_test_macros.hpp>
#include <ncxx/algorithm/find-if.hpp>
#include <ncxx/container/static-array.hpp>

namespace NOS {

TEST_CASE("findIf", "[algorithm]")
{
    auto isEven = [](int v) { return (v % 2) == 0; };
    auto isOdd = [](int v) { return (v % 2) != 0; };

    StaticArray values = toStaticArray<int>({0, 2, 4, 6});

    CHECK(findIf(values.begin(), values.end(), isEven) == values.begin());
    CHECK(findIf(values.begin(), values.end(), isOdd) == values.end());
}

} // namespace NOS
