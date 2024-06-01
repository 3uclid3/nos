#include <kernel/cxx/malloc.hpp>

#include <kernel/def.hpp>
#include <nxx/memory/allocator/stack_allocator.hpp>

namespace nxx {

namespace details {

// lets start with a simple stack allocator
using global_allocator_t = stack_allocator<8196>;

global_allocator_t global_allocator{};

} // namespace details

memory_block allocate(size_t size)
{
    return details::global_allocator.allocate(size);
}

void deallocate(memory_block block)
{
    details::global_allocator.deallocate(block);
}

} // namespace nxx

void* operator new(nxx::size_t size)
{
    nxx::memory_block block = nxx::allocate(size);
    NXX_ASSERT(block.pointer != nullptr);
    return block.pointer;
}

void* operator new[](nxx::size_t size)
{
    nxx::memory_block block = nxx::allocate(size);
    NXX_ASSERT(block.pointer != nullptr);
    return block.pointer;
}

void operator delete(void* ptr) noexcept
{
    // TODO Size
    // affix allocator with the size
    nxx::memory_block block{.pointer = ptr, .size = 0};
    nxx::deallocate(block);
}

void operator delete[](void* ptr) noexcept
{
    // TODO Size
    // affix allocator with the size
    nxx::memory_block block{.pointer = ptr, .size = 0};
    nxx::deallocate(block);
}

void operator delete(void* ptr, nxx::size_t size) noexcept
{
    nxx::memory_block block{.pointer = ptr, .size = size};
    nxx::deallocate(block);
}