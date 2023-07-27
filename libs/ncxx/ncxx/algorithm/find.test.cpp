#include <ncxx/algorithm/find.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/container/static-array.hpp>

namespace NOS {

TEST_CASE("find", "[algorithm]")
{
    StaticArray values = toStaticArray<int>({0, 2, 4, 6});

    CHECK(find(values.begin(), values.end(), 0) == values.begin());
    CHECK(find(values.begin(), values.end(), 1) == values.end());
}

} // namespace NOS
