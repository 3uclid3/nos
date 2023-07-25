#include <catch2/catch_test_macros.hpp>

#include <ncxx/memory/allocator/null-allocator.hpp>

namespace NOS::Memory {

TEST_CASE("NullAllocator::allocate returns nullblk", "[memory]")
{
    NullAllocator allocator;

    CHECK(allocator.allocate(1) == nullblk);
    CHECK(allocator.allocate(10) == nullblk);
    CHECK(allocator.allocate(100) == nullblk);
}

TEST_CASE("NullAllocator::owns", "[memory]")
{
    NullAllocator allocator;

    SECTION("returns true if nullblk")
    {
        CHECK(allocator.owns(nullblk));
    }

    SECTION("returns false")
    {
        CHECK_FALSE(allocator.owns(Block{reinterpret_cast<void*>(0x00001234), 10}));
        CHECK_FALSE(allocator.owns(Block{reinterpret_cast<void*>(0x00004321), 100}));
    }
}

} // namespace NOS::Memory
