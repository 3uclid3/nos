#pragma once

#include <debug/assert.hpp>
#include <memory/block.hpp>

namespace nos::memory {

struct Block;

namespace allocator {

class Null
{
public:
    static constexpr alignment_t Alignment{64};

    constexpr bool owns(Block block) const;

    constexpr Block allocate(size_t size);

    constexpr void deallocate(Block block);
    constexpr void deallocateAll();

    constexpr bool expand(Block& block, size_t size);
    constexpr bool reallocate(Block& block, size_t size);
};

constexpr bool Null::owns(Block block) const
{
    NOS_UNUSED(block);
    return block == nullblk;
}

constexpr Block Null::allocate(size_t size)
{
    NOS_UNUSED(size);
    return nullblk;
}

constexpr void Null::deallocate(Block block)
{
    NOS_UNUSED(block);
    NOS_ASSERT(block == nullblk);
}

constexpr bool Null::expand(Block& block, size_t size)
{
    NOS_UNUSED(block);
    NOS_UNUSED(size);
    NOS_ASSERT(block == nullblk);
    return false;
}

constexpr bool Null::reallocate(Block& block, size_t size)
{
    NOS_UNUSED(block);
    NOS_UNUSED(size);
    NOS_ASSERT(block == nullblk);
    return false;
}

} // namespace allocator
} // namespace nos::memory
