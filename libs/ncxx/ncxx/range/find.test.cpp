#include <ncxx/range/find.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/container/static-array.hpp>

namespace NOS::Range {

TEST_CASE("find", "[range]")
{
    StaticArray values = toStaticArray<int>({0, 2, 4, 6});

    CHECK(find(values, 0) == values.begin());
    CHECK(find(values, 1) == values.end());
}

} // namespace NOS::Range
