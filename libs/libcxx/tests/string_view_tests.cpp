#include <catch2/catch_test_macros.hpp>

#include <string_view.hpp>

namespace nos
{

TEST_CASE("string_view - ctor")
{
    SECTION("cstr")
    {
        const char* my_cstr = "my_cstr";
        const size_t my_cstr_size = sizeof(my_cstr) - 1ULL;

        const string_view cstr{"my_cstr"};

        CHECK(cstr.size() == my_cstr_size);
    }
}

} // namespace nos

