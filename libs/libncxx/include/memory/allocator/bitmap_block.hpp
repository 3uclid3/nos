#pragma once

#include <memory/block.hpp>

namespace nos::memory::allocator {

template<typename Allocator, size_t BlockSize>
class bitmap_block
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

} // namespace nos::memory::allocator
