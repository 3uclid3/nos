#include <catch2/catch_test_macros.hpp>

#include <nos_string.h>
#include <string.h>
#include <utility/asan_buffer.hpp>

TEST_CASE("memset")
{
    static constexpr size_t maximum_size = 510;

    asan_buffer buffer(maximum_size);
    for (std::size_t size = 0; size < maximum_size; ++size)
    {
        const char value = size % 10;

        CHECK(nos_memset(&buffer[0], value, size) == &buffer[0]);

        for (std::size_t i = 0; i < size; ++i)
        {
            CHECK(buffer[i] == value);
        }
    }
}