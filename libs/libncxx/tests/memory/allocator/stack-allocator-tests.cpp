#include <catch2/catch_test_macros.hpp>

#include <memory/allocator/stack-allocator.hpp>

namespace nos::memory {

TEST_CASE("StackAllocator<TSize, TAlignment>::", "[memory]")
{
    using StackAllocator64 = StackAllocator<64>;

    StackAllocator64 allocator;

    SECTION("allocate returns allocated block")
    {
        static constexpr size_t Size = StackAllocator64::Size / 2;

        Block block = allocator.allocate(Size);

        CHECK(block.pointer != nullptr);
        CHECK(block.size == roundToAlignment(Size, StackAllocator64::Alignment));
    }

    SECTION("allocate returns nullblk if not enough memory")
    {
        static constexpr size_t Size = StackAllocator64::Size + 2;

        Block block = allocator.allocate(Size);

        CHECK(block == nullblk);
    }
}

} // namespace nos::memory
