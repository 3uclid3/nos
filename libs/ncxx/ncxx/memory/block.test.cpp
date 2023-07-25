#include <catch2/catch_test_macros.hpp>

#include <ncxx/memory/block.hpp>

namespace NOS::Memory {

TEST_CASE("Block implicit convert to ConstBlock", "[memory]")
{
    ConstBlock constBlock = nullblk;

    CHECK(constBlock == nullblk);
}

} // namespace NOS::Memory
