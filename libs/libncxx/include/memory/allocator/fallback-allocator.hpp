#pragma once

#include <memory/block.hpp>

namespace nos::memory::allocator {

template<typename PrimaryAllocator, typename FallbackAllocator>
class fallback : private PrimaryAllocator, private FallbackAllocator
{
public:
    constexpr bool is_owner(block block) const;

    constexpr block allocate(size_t size);
    constexpr block allocate_all();

    constexpr void deallocate(block block);
    constexpr void deallocate_all();

    constexpr void expand(block& block, size_t delta_size);
    constexpr void reallocate(block& block, size_t size);
};

template<typename PrimaryAllocator, typename FallbackAllocator>
constexpr bool fallback<PrimaryAllocator, FallbackAllocator>::is_owner(block block) const
{
    return PrimaryAllocator::is_owner(block) || FallbackAllocator::is_owner(block);
}

template<typename PrimaryAllocator, typename FallbackAllocator>
constexpr block fallback<PrimaryAllocator, FallbackAllocator>::allocate(size_t size)
{
    block block = PrimaryAllocator::allocate(size);

    if (block.pointer)
    {
        return block;
    }

    return FallbackAllocator::allocate(size);
}

template<typename PrimaryAllocator, typename FallbackAllocator>
constexpr block fallback<PrimaryAllocator, FallbackAllocator>::allocate_all()
{
    block block = PrimaryAllocator::allocate_all();

    if (block.pointer)
    {
        return block;
    }

    return FallbackAllocator::allocate_all();
}

template<typename PrimaryAllocator, typename FallbackAllocator>
constexpr void fallback<PrimaryAllocator, FallbackAllocator>::deallocate(block block)
{
    if (PrimaryAllocator::is_owner_of(block))
    {
        PrimaryAllocator::deallocate(block);
    }
    else
    {
        FallbackAllocator::deallocate(block);
    }
}

template<typename PrimaryAllocator, typename FallbackAllocator>
constexpr void fallback<PrimaryAllocator, FallbackAllocator>::deallocate_all()
{
    PrimaryAllocator::deallocate_all(block);
    FallbackAllocator::deallocate_all(block);
}

} // namespace nos
