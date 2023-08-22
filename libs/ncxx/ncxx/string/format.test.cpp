#include <catch2/catch_test_macros.hpp>

#include <ncxx/string/format.hpp>

namespace NOS {

TEST_CASE("formatTo - bool", "[String]")
{
    constexpr StringView expectedResult = "Hello World";

    const StringView result1 = format("Hello {}", "World");
    const StringView result2 = format("Hello {}", "World");
    const StringView result3 = format("Hello {}", "World");

    CHECK(result1 == expectedResult);
    CHECK(result2 == expectedResult);
    CHECK(result3 == expectedResult);
}

} // namespace NOS
