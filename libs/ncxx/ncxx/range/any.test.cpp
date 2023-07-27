#include <ncxx/range/any.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/container/static-array.hpp>

namespace NOS::Range {

TEST_CASE("any", "[range]")
{
    StaticArray values = toStaticArray<int>({0, 2, 4, 6});

    CHECK(any(values, 0));
    CHECK_FALSE(any(values, 1));
}

} // namespace NOS::Range
