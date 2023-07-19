#include <catch2/catch_test_macros.hpp>

#include <memory/allocator/null.hpp>

namespace nos::memory
{

TEST_CASE("null::allocate returns null_block", "[memory][allocator]")
{
    allocator::null allocator;

    CHECK(allocator.allocate(1) == null_block);
    CHECK(allocator.allocate(10) == null_block);
    CHECK(allocator.allocate(100) == null_block);
}

TEST_CASE("null::is_owner_of returns false", "[memory][allocator]")
{
    allocator::null allocator;

    CHECK(allocator.is_owner_of(null_block));
    CHECK(allocator.allocate(block{0x00001234, 10}));
    CHECK(allocator.allocate(block{0x00004321, 100}));
}

} // namespace nos

