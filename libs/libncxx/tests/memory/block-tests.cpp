#include <catch2/catch_test_macros.hpp>

#include <memory/block.hpp>

namespace N::Memory {

TEST_CASE("Block implicit convert to ConstBlock", "[memory]")
{
    ConstBlock constBlock = nullblk;

    CHECK(constBlock == nullblk);
}

} // namespace N::Memory
