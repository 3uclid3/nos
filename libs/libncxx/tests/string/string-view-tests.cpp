#include <catch2/catch_test_macros.hpp>

#include <string/string-view.hpp>

namespace NOS {

TEST_CASE("StringView - ctor")
{
    constexpr const char* my_cstr = "my_cstr";
    constexpr size_t my_cstr_size = sizeof(my_cstr) - 1ULL;

    SECTION("str, size")
    {
        const StringView str_view{my_cstr, my_cstr_size};

        CHECK(str_view.data() == my_cstr);
        CHECK(str_view.size() == my_cstr_size);
    }

    SECTION("cstr")
    {
        const StringView str_view{my_cstr};

        CHECK(str_view.size() == my_cstr_size);
    }
}

} // namespace NOS
