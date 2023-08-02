#include <ncxx/algorithm/clamp.hpp>

#include <catch2/catch_test_macros.hpp>

namespace NOS {

TEST_CASE("clamp", "[Algorithm]")
{
    CHECK(clamp(-1, 0, 9) == 0);
    CHECK(clamp(4, 0, 9) == 4);
    CHECK(clamp(10, 0, 9) == 9);
}

TEST_CASE("clamp functor", "[Algorithm]")
{
    auto isLess = [](int lhs, int rhs) { return lhs < rhs; };

    CHECK(clamp(-1, 0, 9, isLess) == 0);
    CHECK(clamp(4, 0, 9, isLess) == 4);
    CHECK(clamp(10, 0, 9, isLess) == 9);
}

} // namespace NOS