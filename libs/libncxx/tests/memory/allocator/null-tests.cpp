#include <catch2/catch_test_macros.hpp>

#include <memory/allocator/null.hpp>

namespace nos::memory
{

TEST_CASE("Null::allocate returns nullblk", "[memory][allocator]")
{
    allocator::Null allocator;

    CHECK(allocator.allocate(1) == nullblk);
    CHECK(allocator.allocate(10) == nullblk);
    CHECK(allocator.allocate(100) == nullblk);
}

TEST_CASE("Null::owns", "[memory][allocator]")
{
    allocator::Null allocator;

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

} // namespace nos

