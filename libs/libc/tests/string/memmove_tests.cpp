#include <catch2/catch_test_macros.hpp>

#include <nos_string.h>
#include <string.h>
#include <utility/asan_buffer.hpp>

TEST_CASE("memmove - zero byte")
{
    constexpr size_t size = 6;
    char buffer[size] = {'4', '2', '0', '0', '2', '4'};
    const char expected[size] = {'4', '2', '0', '0', '2', '4'};

    void* dest = buffer;
    const void* result = nos_memmove(dest, buffer + 2, 0);

    CHECK(dest == result);
    CHECK(memcmp(buffer, expected, size) == 0);
}

TEST_CASE("memmove - source and destination have the same address")
{
    constexpr size_t size = 6;
    char buffer[size] = {'4', '2', '0', '0', '2', '4'};
    const char expected[size] = {'4', '2', '0', '0', '2', '4'};

    void* dest = buffer;
    const void* result = nos_memmove(dest, buffer, 1);

    CHECK(dest == result);
    CHECK(memcmp(buffer, expected, size) == 0);
}

TEST_CASE("memmove - source start before destination")
{
    constexpr size_t size = 5;
    char buffer[size] = {'z', '2', '3', '4', 'z'};
    const char expected[size] = {'z', '2', '2', '3', 'z'};

    void* dest = buffer + 2;
    const void* result = nos_memmove(dest, buffer + 1, 2);

    CHECK(dest == result);
    CHECK(memcmp(buffer, expected, size) == 0);
}

TEST_CASE("memmove - source start after destination")
{
    constexpr size_t size = 5;
    char buffer[size] = {'z', '2', '3', '4', 'z'};
    const char expected[size] = {'z', '3', '4', '4', 'z'};

    void* dest = buffer + 1;
    const void* result = nos_memmove(dest, buffer + 2, 2);

    CHECK(dest == result);
    CHECK(memcmp(buffer, expected, size) == 0);
}