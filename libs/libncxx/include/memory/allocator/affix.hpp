#pragma once

#include <memory/block.hpp>

namespace nos::memory::allocator {

template<typename Allocator, typename Prefix, typename Suffix = void>
class affix
{
public:
    bool is_owner_of(memory_block block) const;

    memory_block allocate(size_t size);

    void deallocate(memory_block block);
};

} // namespace nos::memory::allocator
