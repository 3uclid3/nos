#pragma once

#include <memory/block.hpp>

namespace nos::memory {

struct block;

namespace allocator {

class null
{
public:
    constexpr bool is_owner(block block) const;

    constexpr block allocate(size_t size);

    constexpr void deallocate(block block);
    constexpr void deallocate_all();

    constexpr void expand(block& block, size_t delta_size);
    constexpr void reallocate(block& block, size_t size);
};

constexpr bool null::is_owner(block block) const
{
    NOS_UNUSED(block);
    return false;
}

constexpr block null::allocate(size_t size)
{
    NOS_UNUSED(size);
    return null_block;
}

constexpr void null::deallocate(block block)
{
    NOS_UNUSED(block);
}

constexpr void null::expand(block& block, size_t delta_size)
{
    NOS_UNUSED(block);
    NOS_UNUSED(delta_size);
}

constexpr void null::reallocate(block& block, size_t size)
{
    NOS_UNUSED(block);
    NOS_UNUSED(size);
}

} // namespace allocator
} // namespace nos::memory
