#pragma once

#include <debug/assert.hpp>
#include <def.hpp>
#include <memory/block.hpp>

namespace NOS::Memory {

struct Block;

class NullAllocator
{
public:
    static constexpr alignment_t Alignment{64};

    constexpr bool owns(ConstBlock block) const;

    constexpr Block allocate(size_t size);

    constexpr void deallocate(Block block);
    constexpr void deallocateAll();

    constexpr Block expand(Block block, size_t size);
    constexpr Block reallocate(Block block, size_t size);
};

constexpr bool NullAllocator::owns(ConstBlock block) const
{
    NOS_UNUSED(block);
    return block == nullblk;
}

constexpr Block NullAllocator::allocate(size_t size)
{
    NOS_UNUSED(size);
    return nullblk;
}

constexpr void NullAllocator::deallocate(Block block)
{
    NOS_UNUSED(block);
    NOS_ASSERT(block == nullblk);
}

constexpr Block NullAllocator::expand(Block block, size_t size)
{
    NOS_UNUSED(block);
    NOS_UNUSED(size);
    NOS_ASSERT(block == nullblk);
    return nullblk;
}

constexpr Block NullAllocator::reallocate(Block block, size_t size)
{
    NOS_UNUSED(block);
    NOS_UNUSED(size);
    NOS_ASSERT(block == nullblk);
    return nullblk;
}

} // namespace NOS::Memory
