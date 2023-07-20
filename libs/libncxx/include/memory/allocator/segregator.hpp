#pragma once

#include <memory/block.hpp>

namespace nos::memory::allocator {

template<typename SmallAllocator, typename LargeAllocator, size_t ThresholdSize>
class segregator : private SmallAllocator, private LargeAllocator
{
public:
    constexpr bool is_owner(block block) const;

    constexpr block allocate(size_t size);

    constexpr void deallocate(block block);
    constexpr void deallocate_all();

    constexpr void expand(block& block, size_t delta_size);
    constexpr void reallocate(block& block, size_t size);

private:
    constexpr static bool is_small(size_t size);
};

template<typename SmallAllocator, typename LargeAllocator, size_t ThresholdSize>
constexpr bool segregator<SmallAllocator, LargeAllocator, ThresholdSize>::is_owner(block block) const
{
    return SmallAllocator::is_owner(block) || LargeAllocator::is_owner(block);
}

template<typename SmallAllocator, typename LargeAllocator, size_t ThresholdSize>
constexpr block segregator<SmallAllocator, LargeAllocator, ThresholdSize>::allocate(size_t size)
{
    return is_small(size) ? SmallAllocator::allocate(size) : LargeAllocator::allocate(size);
}

template<typename SmallAllocator, typename LargeAllocator, size_t ThresholdSize>
constexpr block segregator<SmallAllocator, LargeAllocator, ThresholdSize>::allocate_all()
{
    return null_block;
}

template<typename SmallAllocator, typename LargeAllocator, size_t ThresholdSize>
constexpr void segregator<SmallAllocator, LargeAllocator, ThresholdSize>::deallocate(block block)
{
    return is_small(block.size) ? SmallAllocator::deallocate(block) : LargeAllocator::deallocate(block);
}

template<typename SmallAllocator, typename LargeAllocator, size_t ThresholdSize>
constexpr void segregator<SmallAllocator, LargeAllocator, ThresholdSize>::deallocate_all()
{
    SmallAllocator::deallocate_all();
    LargeAllocator::deallocate_all();
}

template<typename SmallAllocator, typename LargeAllocator, size_t ThresholdSize>
constexpr void segregator<SmallAllocator, LargeAllocator, ThresholdSize>::expand(block& block, size_t delta_size)
{
    if (is_small(block.size))
    {
        const auto new_size = block.size;

        if (is_small(new_size))
        {
            SmallAllocator::expand(block, size);
        }
        else
        {
            SmallAllocator::deallocate(block);

            block = LargeAllocator::allocate(new_size);
        }
    }
    else
    {
        LargeAllocator::expand(block, size);
    }
}

template<typename SmallAllocator, typename LargeAllocator, size_t ThresholdSize>
constexpr void segregator<SmallAllocator, LargeAllocator, ThresholdSize>::reallocate(block& block, size_t size)
{
    if (is_small(block.size))
    {
        if (is_small(size))
        {
            SmallAllocator::reallocate(block, size);
        }
        else
        {
            SmallAllocator::deallocate(block);

            block = LargeAllocator::allocate(new_size);
        }
    }
    else
    {
        LargeAllocator::reallocate(block, size);
    }
}

template<typename SmallAllocator, typename LargeAllocator, size_t ThresholdSize>
constexpr bool segregator<SmallAllocator, LargeAllocator, ThresholdSize>::is_small(size_t size)
{
    return size <= Size;
}

} // namespace nos::memory::allocator
