#include <ncxx/algorithm/any-of.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/container/static-array.hpp>

namespace NOS {

TEST_CASE("anyOf", "[algorithm]")
{
    StaticArray values = toStaticArray<int>({1, 2, 3, 3});

    auto isTwo = [](int v) { return v == 2; };
    auto isFour = [](int v) { return v == 4; };

    CHECK(anyOf(values.begin(), values.end(), isTwo));
    CHECK_FALSE(anyOf(values.begin(), values.end(), isFour));
}

} // namespace NOS
