#include <ncxx/utility/scope-exit.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/basic-types.hpp>

namespace NOS {

TEST_CASE("ScopeExit", "[system][utility]")
{
    size_t count = 0;

    {
        auto scope = makeScopeExit([&count]() { ++count; });
    }

    CHECK(count == 1);
}

} // namespace NOS