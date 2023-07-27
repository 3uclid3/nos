#include <ncxx/algorithm/none-of.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/container/static-array.hpp>

namespace NOS {

TEST_CASE("noneOf", "[algorithm]")
{
    StaticArray values = toStaticArray<int>({1, 1, 3, 4});

    auto isTwo = [](int v) { return v == 2; };
    auto isFour = [](int v) { return v == 4; };

    CHECK(noneOf(values.begin(), values.end(), isTwo));
    CHECK_FALSE(noneOf(values.begin(), values.end(), isFour));
}

} // namespace NOS
