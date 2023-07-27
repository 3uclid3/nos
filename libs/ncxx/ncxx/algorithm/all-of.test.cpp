#include <ncxx/algorithm/all-of.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/container/static-array.hpp>

namespace NOS {

TEST_CASE("allOf", "[algorithm]")
{
    StaticArray values = toStaticArray<int>({2, 2, 2, 2});

    auto isTwo = [](int v) { return v == 2; };
    auto isFour = [](int v) { return v == 4; };

    CHECK(allOf(values.begin(), values.end(), isTwo));
    CHECK_FALSE(allOf(values.begin(), values.end(), isFour));
}

} // namespace NOS
