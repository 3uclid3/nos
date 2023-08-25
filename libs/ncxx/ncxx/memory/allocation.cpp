#include <ncxx/memory/allocation.hpp>

#include <ncxx/memory/block.hpp>

#ifdef NOS_NATIVE

extern "C" {

extern void* malloc(size_t size);
extern void* realloc(void* ptr, size_t size);
extern void free(void* ptr);

} // extern "C"

namespace NOS::Memory {

Block allocate(size_t size)
{
    return Block{::malloc(size), size};
}

Block reallocate(Block block, size_t size)
{
    return Block{::realloc(block.pointer, size), size};
}

void deallocate(Block block)
{
    ::free(block.pointer);
}

} // namespace NOS::Memory

#endif