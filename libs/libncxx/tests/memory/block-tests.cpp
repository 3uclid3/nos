#include <catch2/catch_test_macros.hpp>

#include <memory/block.hpp>

namespace nos::memory
{

TEST_CASE("Block implicit convert to ConstBlock", "[memory]")
{
    ConstBlock constBlock = nullblk;

    CHECK(constBlock == nullblk);
}

} // namespace nos

