#include <catch2/catch_test_macros.hpp>

#include <string/format.hpp>

namespace NOS {

TEST_CASE("formatTo - bool", "[String]")
{
    CHECK(format("Hello {}", "World") == "Hello World");
    CHECK(format("{} World", "Hello") == "Hello World");
    CHECK(format("{} {}", "Hello", "World") == "Hello World");
}

}
