#include <catch2/catch_test_macros.hpp>

#include <ncxx/string/format.hpp>

namespace NOS {

TEST_CASE("format - circling buffer", "[String]")
{
    constexpr StringView expectedResult = "Hello World";

    const StringView result1 = format("Hello {}", "World");
    const StringView result2 = format("{} World", "Hello");
    const StringView result3 = format("Hel{}rld", "lo Wo");

    CHECK(result1 == expectedResult);
    CHECK(result2 == expectedResult);
    CHECK(result3 == expectedResult);
}

} // namespace NOS
