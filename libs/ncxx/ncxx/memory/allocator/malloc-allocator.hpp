#pragma once

#include <ncxx/basic-types.hpp>

namespace NOS::Memory {

struct Block;
struct ConstBlock;

class MallocAllocator
{
public:
    bool owns(ConstBlock block) const;

    Block allocate(size_t size);

    void deallocate(Block block);
    void deallocateAll();

    Block expand(Block block, size_t size);
    Block reallocate(Block block, size_t size);
};

} // namespace NOS::Memory
