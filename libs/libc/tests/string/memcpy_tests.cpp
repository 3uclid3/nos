#include <catch2/catch_test_macros.hpp>

#include <nos_string.h>
#include <string.h>
#include <utility/asan_buffer.hpp>

TEST_CASE("memcpy")
{
    static constexpr size_t maximum_size = 510;

    asan_buffer source(maximum_size);
    asan_buffer destination(maximum_size);

    source.initialize(1);

    for (size_t i = 0; i < maximum_size; ++i)
    {
        destination.initialize(2);

        nos_memcpy(destination.begin(), source.begin(), i);

        for (size_t j = 0; j < i; ++j)
        {
            CHECK(source[j] == destination[j]);
        }
    }
}