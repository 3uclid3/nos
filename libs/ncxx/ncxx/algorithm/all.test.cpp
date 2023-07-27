#include <ncxx/algorithm/all.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/container/static-array.hpp>

namespace NOS {

TEST_CASE("all", "[algorithm]")
{
    StaticArray values = toStaticArray<int>({2, 2, 2, 2});

    CHECK(all(values.begin(), values.end(), 2));
    CHECK_FALSE(all(values.begin(), values.end(), 1));
}

} // namespace NOS
