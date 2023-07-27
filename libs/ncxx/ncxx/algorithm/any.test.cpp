#include <ncxx/algorithm/any.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/container/static-array.hpp>

namespace NOS {

TEST_CASE("any", "[algorithm]")
{
    StaticArray values = toStaticArray<int>({0, 2, 4, 6});

    CHECK(any(values.begin(), values.end(), 0));
    CHECK_FALSE(any(values.begin(), values.end(), 1));
}

} // namespace NOS
