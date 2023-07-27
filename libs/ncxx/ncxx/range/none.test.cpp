#include <ncxx/range/none.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/container/static-array.hpp>

namespace NOS::Range {

TEST_CASE("none", "[range]")
{
    StaticArray values = toStaticArray<int>({1, 2, 3, 5});

    CHECK(none(values, 4));
    CHECK_FALSE(none(values, 1));
}

} // namespace NOS::Range
