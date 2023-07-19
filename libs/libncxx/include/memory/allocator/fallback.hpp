#pragma once

#include <memory/block.hpp>

namespace nos {

template<typename PrimaryAllocator, typename FallbackAllocator>
class fallback_allocator : private PrimaryAllocator, private FallbackAllocator
{
public:
    bool is_owner_of(memory_block block) const;

    memory_block allocate(size_t size);

    void deallocate(memory_block block);
};

template<typename PrimaryAllocator, typename FallbackAllocator>
bool fallback_allocator<PrimaryAllocator, FallbackAllocator>::is_owner_of(memory_block block) const
{
    return PrimaryAllocator::is_owner_of(block) || FallbackAllocator::is_owner_of(block);
}

template<typename PrimaryAllocator, typename FallbackAllocator>
memory_block fallback_allocator<PrimaryAllocator, FallbackAllocator>::allocate(size_t size)
{
    memory_block block = PrimaryAllocator::allocate(size);

    if (block.pointer)
    {
        return block;
    }

    return FallbackAllocator::allocate(size);
}

template<typename PrimaryAllocator, typename FallbackAllocator>
void fallback_allocator<PrimaryAllocator, FallbackAllocator>::deallocate(memory_block block)
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

} // namespace nos
