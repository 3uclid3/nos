#include <ncxx/algorithm/none.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/container/static-array.hpp>

namespace NOS {

TEST_CASE("none", "[algorithm]")
{
    StaticArray values = toStaticArray<int>({1, 2, 3, 5});

    CHECK(none(values.begin(), values.end(), 4));
    CHECK_FALSE(none(values.begin(), values.end(), 1));
}

} // namespace NOS
