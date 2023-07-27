#include <ncxx/range/all.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/container/static-array.hpp>

namespace NOS::Range {

TEST_CASE("all", "[range]")
{
    StaticArray values = toStaticArray<int>({2, 2, 2, 2});

    CHECK(all(values, 2));
    CHECK_FALSE(all(values, 1));
}

} // namespace NOS
