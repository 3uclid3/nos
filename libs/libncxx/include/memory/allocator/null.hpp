#pragma once

#include <memory/block.hpp>

namespace nos::memory {

struct block;

namespace allocator {

class null
{
public:
    static constexpr alignment_t alignment{default_alignment};

    bool is_owner(block block) const;

    block allocate(size_t size);
    block allocate_all();

    void deallocate(block block);
    void deallocate_all();

    void expand(block& block, size_t delta_size);
    void reallocate(block& block, size_t size);
};

bool null::is_owner(block block) const
{
    NOS_UNUSED(block);
    return false;
}

block null::allocate(size_t size)
{
    NOS_UNUSED(size);
    return null_block;
}

block null::allocate_all()
{
    return null_block;
}

void null::deallocate(block block)
{
    NOS_UNUSED(block);
}

void null::expand(block& block, size_t delta_size)
{
    NOS_UNUSED(block);
    NOS_UNUSED(delta_size);
}

void null::reallocate(block& block, size_t size)
{
    NOS_UNUSED(block);
    NOS_UNUSED(size);
}

} // namespace allocator
} // namespace nos::memory
