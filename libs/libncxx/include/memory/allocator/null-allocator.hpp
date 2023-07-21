#pragma once

#include <debug/assert.hpp>
#include <memory/block.hpp>

namespace N::Memory {

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
    N_UNUSED(block);
    return block == nullblk;
}

constexpr Block NullAllocator::allocate(size_t size)
{
    N_UNUSED(size);
    return nullblk;
}

constexpr void NullAllocator::deallocate(Block block)
{
    N_UNUSED(block);
    N_ASSERT(block == nullblk);
}

constexpr Block NullAllocator::expand(Block block, size_t size)
{
    N_UNUSED(block);
    N_UNUSED(size);
    N_ASSERT(block == nullblk);
    return nullblk;
}

constexpr Block NullAllocator::reallocate(Block block, size_t size)
{
    N_UNUSED(block);
    N_UNUSED(size);
    N_ASSERT(block == nullblk);
    return nullblk;
}

} // namespace N::Memory
