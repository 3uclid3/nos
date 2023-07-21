#pragma once

#include <memory/block.hpp>

namespace NOS::Memory {

template<typename TSmallAllocator, typename TLargeAllocator, size_t TThresholdSize>
class SegregatorAllocator : private TSmallAllocator, private TLargeAllocator
{
public:
    using SmallAllocator = TSmallAllocator;
    using LargeAllocator = TLargeAllocator;

    static constexpr size_t ThresholdSize = TThresholdSize;

    constexpr bool owns(ConstBlock block) const;

    constexpr Block allocate(size_t size);

    constexpr void deallocate(Block block);
    constexpr void deallocateAll();

    constexpr Block expand(Block block, size_t size);
    constexpr Block reallocate(Block block, size_t size);

private:
    static constexpr bool isSmall(size_t size);
};

template<typename TSmallAllocator, typename TLargeAllocator, size_t ThresholdSize>
constexpr bool SegregatorAllocator<TSmallAllocator, TLargeAllocator, ThresholdSize>::owns(ConstBlock block) const
{
    return SmallAllocator::owns(block) || LargeAllocator::owns(block);
}

template<typename TSmallAllocator, typename TLargeAllocator, size_t ThresholdSize>
constexpr Block SegregatorAllocator<TSmallAllocator, TLargeAllocator, ThresholdSize>::allocate(size_t size)
{
    return isSmall(size) ? SmallAllocator::allocate(size) : TLargeAllocator::allocate(size);
}

template<typename TSmallAllocator, typename TLargeAllocator, size_t ThresholdSize>
constexpr void SegregatorAllocator<TSmallAllocator, TLargeAllocator, ThresholdSize>::deallocate(Block block)
{
    return isSmall(block.size) ? TSmallAllocator::deallocate(block) : TLargeAllocator::deallocate(block);
}

template<typename TSmallAllocator, typename TLargeAllocator, size_t ThresholdSize>
constexpr void SegregatorAllocator<TSmallAllocator, TLargeAllocator, ThresholdSize>::deallocateAll()
{
    SmallAllocator::deallocateAll();
    LargeAllocator::deallocateAll();
}

template<typename TSmallAllocator, typename TLargeAllocator, size_t ThresholdSize>
constexpr Block SegregatorAllocator<TSmallAllocator, TLargeAllocator, ThresholdSize>::expand(Block block, size_t size)
{
    if (isSmall(block.size))
    {
        const size_t newSize = block.size + size;

        if (isSmall(newSize))
        {
            return SmallAllocator::expand(block, size);
        }
        else
        {
            SmallAllocator::deallocate(block);

            return LargeAllocator::allocate(newSize);
        }
    }

    return LargeAllocator::expand(block, size);
}

template<typename TSmallAllocator, typename TLargeAllocator, size_t ThresholdSize>
constexpr Block SegregatorAllocator<TSmallAllocator, TLargeAllocator, ThresholdSize>::reallocate(Block block, size_t size)
{
    if (isSmall(block.size))
    {
        if (isSmall(size))
        {
            return SmallAllocator::reallocate(block, size);
        }
        else
        {
            SmallAllocator::deallocate(block);

            return LargeAllocator::allocate(size);
        }
    }

    return LargeAllocator::reallocate(block, size);
}

template<typename TSmallAllocator, typename TLargeAllocator, size_t ThresholdSize>
constexpr bool SegregatorAllocator<TSmallAllocator, TLargeAllocator, ThresholdSize>::isSmall(size_t size)
{
    return size <= Size;
}

} // namespace NOS::Memory
