#pragma once

#include <memory/block.hpp>

namespace nos {

// [min, min + step]
// [min + step, min + 2 * step]

template<typename Allocator, size_t Min, size_t Max, size_t Step>
class bucketizer_allocator
{
public:
    bool is_owner_of(memory_block block) const;

    memory_block allocate(size_t size);

    void deallocate(memory_block block);
};

} // namespace nos
