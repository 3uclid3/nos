#include <ncxx/range/none-of.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/container/static-array.hpp>

namespace NOS::Range {

TEST_CASE("noneOf", "[range]")
{
    StaticArray values = toStaticArray<int>({1, 1, 3, 4});

    auto isTwo = [](int v) { return v == 2; };
    auto isFour = [](int v) { return v == 4; };

    CHECK(noneOf(values, isTwo));
    CHECK_FALSE(noneOf(values, isFour));
}

} // namespace NOS::Range
