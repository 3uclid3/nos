#pragma once

#include <ncxx/memory/block.hpp>

namespace NOS::Memory {

template<typename TPrimaryAllocator, typename TFallbackAllocator>
class FallbackAllocator : private TPrimaryAllocator, private TFallbackAllocator
{
public:
    using PrimaryAllocator = TPrimaryAllocator;
    using FallbackAllocator = TFallbackAllocator;

    constexpr bool owns(ConstBlock block) const;

    constexpr Block allocate(size_t size);

    constexpr void deallocate(Block block);
    constexpr void deallocateAll();

    constexpr Block expand(Block block, size_t size);
    constexpr Block reallocate(Block block, size_t size);
};

template<typename TPrimaryAllocator, typename TFallbackAllocator>
constexpr bool FallbackAllocator<TPrimaryAllocator, TFallbackAllocator>::owns(ConstBlock block) const
{
    return PrimaryAllocator::owns(block) || FallbackAllocator::owns(block);
}

template<typename TPrimaryAllocator, typename TFallbackAllocator>
constexpr Block FallbackAllocator<TPrimaryAllocator, TFallbackAllocator>::allocate(size_t size)
{
    Block block = PrimaryAllocator::allocate(size);

    if (block != nullblk)
    {
        return block;
    }

    return FallbackAllocator::allocate(size);
}

template<typename TPrimaryAllocator, typename TFallbackAllocator>
constexpr void FallbackAllocator<TPrimaryAllocator, TFallbackAllocator>::deallocate(Block block)
{
    if (PrimaryAllocator::owns(block))
    {
        PrimaryAllocator::deallocate(block);
    }
    else
    {
        FallbackAllocator::deallocate(block);
    }
}

template<typename TPrimaryAllocator, typename TFallbackAllocator>
constexpr void FallbackAllocator<TPrimaryAllocator, TFallbackAllocator>::deallocateAll()
{
    PrimaryAllocator::deallocateAll();
    FallbackAllocator::deallocateAll();
}

template<typename TPrimaryAllocator, typename TFallbackAllocator>
constexpr Block FallbackAllocator<TPrimaryAllocator, TFallbackAllocator>::expand(Block block, size_t size)
{
    if (PrimaryAllocator::owns(block))
    {
        Block expandedBlock = PrimaryAllocator::expand(block, size);

        if (expandedBlock != nullblk)
        {
            return expandedBlock;
        }

        // try allocating with the fallback
        Block newBlock = FallbackAllocator::allocate(block.size + size);

        if (newBlock != nullblk)
        {
            copy(newBlock, block, block.size);

            PrimaryAllocator::deallocate(block);
        }

        return newBlock;
    }

    return FallbackAllocator::expand(block, size);
}

template<typename TPrimaryAllocator, typename TFallbackAllocator>
constexpr Block FallbackAllocator<TPrimaryAllocator, TFallbackAllocator>::reallocate(Block block, size_t size)
{
    if (PrimaryAllocator::owns(block))
    {
        Block reallocatedBlock = PrimaryAllocator::reallocate(block, size);

        if (reallocatedBlock != nullblk)
        {
            return reallocatedBlock;
        }

        // try allocating with the fallback
        Block newBlock = FallbackAllocator::allocate(size);

        if (newBlock != nullblk)
        {
            copy(newBlock, block, block.size);

            PrimaryAllocator::deallocate(block);
        }

        return newBlock;
    }

    return FallbackAllocator::reallocate(block, size);
}

} // namespace NOS::Memory
