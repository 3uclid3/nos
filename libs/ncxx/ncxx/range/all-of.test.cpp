#include <ncxx/range/all-of.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/container/static-array.hpp>

namespace NOS::Range {

TEST_CASE("allOf", "[range]")
{
    StaticArray values = toStaticArray<int>({2, 2, 2, 2});

    auto isTwo = [](int v) { return v == 2; };
    auto isFour = [](int v) { return v == 4; };

    CHECK(allOf(values, isTwo));
    CHECK_FALSE(allOf(values, isFour));
}

} // namespace NOS::Range
