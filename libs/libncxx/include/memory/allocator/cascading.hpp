#pragma once

#include <memory/block.hpp>

namespace nos {

template<typename Creator>
class cascading_allocator
{
public:
    bool is_owner_of(memory_block block) const;

    memory_block allocate(size_t size);

    void deallocate(memory_block block);
};

} // namespace nos
