#include <catch2/catch_test_macros.hpp>

#include <nos_string.h>
#include <string.h>
#include <utility/asan_buffer.hpp>

TEST_CASE("memcmp - zero byte")
{
    const char* lhs = "42";
    const char* rhs = "24";

    CHECK(nos_memcmp(lhs, rhs, 0) == 0);
}

TEST_CASE("memcmp - lhs and rhs are the same")
{
    const char* lhs = "42";
    const char* rhs = "42";

    CHECK(nos_memcmp(lhs, rhs, 2) == 0);
}

TEST_CASE("memcmp - lhs is before rhs lexically")
{
    const char* lhs = "42";
    const char* rhs = "43";

    CHECK(nos_memcmp(lhs, rhs, 2) == -1);
}

TEST_CASE("memcmp - lhs is after rhs lexically")
{
    const char* lhs = "42";
    const char* rhs = "41";

    CHECK(nos_memcmp(lhs, rhs, 2) == 1);
}

TEST_CASE("memcmp - equals")
{
    static constexpr std::size_t maximum_size = 400;

    asan_buffer buffer1(maximum_size);
    asan_buffer buffer2(maximum_size);

    buffer1.initialize();
    buffer2.initialize();

    for (std::size_t size = 0; size < maximum_size; ++size)
    {
        CHECK(nos_memcmp(buffer1.begin(), buffer2.begin(), size) == 0);
    }

    for (std::size_t size = 1; size < maximum_size; ++size)
    {
        for (std::size_t i = 0; i < size; ++i)
        {
            const auto cached_buffer2_val = buffer2[i];

            ++buffer2[i];

            // our memcmp is not optimal, can't compare values for now
            bool expected_result = memcmp(buffer1.begin() + i, buffer2.begin() + i, size) > 0;
            bool result = nos_memcmp(buffer1.begin() + i, buffer2.begin() + i, size) > 0; 

            CHECK(result == expected_result);

            buffer2[i] -= 2;

            // our memcmp is not optimal, can't compare values for now
            expected_result = memcmp(buffer1.begin() + i, buffer2.begin() + i, size) < 0;
            result = nos_memcmp(buffer1.begin() + i, buffer2.begin() + i, size) < 0; 

            CHECK(result == expected_result);

            buffer2[i] = cached_buffer2_val;
        }
    }
}
