#include <ncxx/memory/allocator/malloc-allocator.hpp>

#include <ncxx/memory/block.hpp>
#include <ncxx/preprocessor/unused.hpp>

extern "C" {
extern void* malloc(size_t __size);
extern void* realloc(void* __ptr, size_t __size);
extern void free(void* __ptr);
}

namespace NOS::Memory {

bool MallocAllocator::owns(ConstBlock block) const
{
    NOS_UNUSED(block);
    return true;
}

Block MallocAllocator::allocate(size_t size)
{
    return Block{malloc(size), size};
}

void MallocAllocator::deallocate(Block block)
{
    free(block.pointer);
}

void MallocAllocator::deallocateAll()
{
}

Block MallocAllocator::expand(Block block, size_t size)
{
    NOS_UNUSED(block);
    NOS_UNUSED(size);
    return nullblk;
}

Block MallocAllocator::reallocate(Block block, size_t size)
{
    return Block{realloc(block.pointer, size), size};
}

} // namespace NOS::Memory
