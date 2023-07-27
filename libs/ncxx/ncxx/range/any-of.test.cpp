#include <ncxx/range/any-of.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/container/static-array.hpp>

namespace NOS::Range {

TEST_CASE("anyOf", "[range]")
{
    StaticArray values = toStaticArray<int>({1, 2, 3, 3});

    auto isTwo = [](int v) { return v == 2; };
    auto isFour = [](int v) { return v == 4; };

    CHECK(anyOf(values, isTwo));
    CHECK_FALSE(anyOf(values, isFour));
}

} // namespace NOS::Range
