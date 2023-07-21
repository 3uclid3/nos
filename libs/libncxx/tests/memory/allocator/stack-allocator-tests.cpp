#include <catch2/catch_test_macros.hpp>

#include <memory/allocator/stack-allocator.hpp>

namespace N::Memory {

using StackAllocator64 = StackAllocator<64>;

TEST_CASE("StackAllocator::allocate", "[memory]")
{
    StackAllocator64 allocator64;

    SECTION("returns block if size < stack size")
    {
        Block block = allocator64.allocate(StackAllocator64::Size - 2);

        CHECK(block != nullblk);
    }

    SECTION("returns block if size == stack size")
    {
        Block block = allocator64.allocate(StackAllocator64::Size);

        CHECK(block != nullblk);
    }

    SECTION("returns block if size is 0")
    {
        Block block = allocator64.allocate(0);

        CHECK(block == nullblk);
    }

    SECTION("returns nullblk if size > stack size")
    {
        Block block = allocator64.allocate(StackAllocator64::Size + 1);

        CHECK(block == nullblk);
    }

    SECTION("returns nullblk if size > remaining stack size")
    {
        Block block = allocator64.allocate(1);

        REQUIRE(block != nullblk);

        block = allocator64.allocate(StackAllocator64::Size);

        CHECK(block == nullblk);
    }

    SECTION("returns nullblk if size > remaining stack size")
    {
        Block block = allocator64.allocate(StackAllocator64::Size - 1);

        REQUIRE(block != nullblk);

        block = allocator64.allocate(2);

        CHECK(block == nullblk);
    }

    SECTION("returns nullblk if stack empty")
    {
        Block block = allocator64.allocate(StackAllocator64::Size);

        REQUIRE(block != nullblk);

        block = allocator64.allocate(1);

        CHECK(block == nullblk);
    }
}

TEST_CASE("StackAllocator::deallocate", "[memory]")
{
    // fill the allocator and use that information to verify the deallocation has succeeded
    static constexpr size_t Size = StackAllocator64::Size / 2;

    StackAllocator64 allocator;

    Block firstBlock = allocator.allocate(Size);
    Block lastBlock = allocator.allocate(Size);

    REQUIRE(firstBlock != nullblk);
    REQUIRE(lastBlock != nullblk);

    SECTION("if last allocated block")
    {
        allocator.deallocate(lastBlock);

        Block newBlock = allocator.allocate(Size);

        CHECK(newBlock == lastBlock);
    }

    SECTION("nothing not last allocated block")
    {
        allocator.deallocate(firstBlock);

        Block newBlock = allocator.allocate(Size);

        // allocator was full
        CHECK(newBlock == nullblk);
    }
}

} // namespace N::Memory
