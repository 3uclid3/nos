#pragma once

#include <memory/block.hpp>

namespace nos {

template<typename Creator>
class cascading_allocator
{
public:
    constexpr bool is_owner(block block) const;

    constexpr block allocate(size_t size);

    constexpr void deallocate(block block);
    constexpr void deallocate_all();

    constexpr void expand(block& block, size_t delta_size);
    constexpr void reallocate(block& block, size_t size);
};

} // namespace nos
