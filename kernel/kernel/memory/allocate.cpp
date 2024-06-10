#include <kernel/memory/allocate.hpp>

#include <nxx/memory/allocator/prefixed_size_allocator.hpp>
#include <nxx/memory/allocator/stack_allocator.hpp>

namespace nxx {

namespace details {

// lets start with a simple stack allocator
using global_allocator_t = prefixed_size_allocator<stack_allocator<8196>>;

global_allocator_t global_allocator{};

} // namespace details

memory_block allocate(size_t size)
{
    return details::global_allocator.allocate(size);
}

bool expand_allocate(memory_block& block, size_t delta)
{
    return details::global_allocator.expand(block, delta);
}

bool reallocate(memory_block& block, size_t new_size)
{
    return details::global_allocator.reallocate(block, new_size);
}

void deallocate(memory_block& block)
{
    details::global_allocator.deallocate(block);
}

} // namespace nxx

/*
void* operator new(nxx::size_t size)
{
    return nxx::allocate(size).ptr;
}

void* operator new[](nxx::size_t size)
{
    return nxx::allocate(size).ptr;
}

void operator delete(void* ptr) noexcept
{
    nxx::memory_block block{ptr, 0};
    nxx::deallocate(block);
}

void operator delete[](void* ptr) noexcept
{
    nxx::memory_block block{ptr, 0};
    nxx::deallocate(block);
}

void operator delete(void* ptr, nxx::size_t size) noexcept
{
    nxx::memory_block block{ptr, size};
    nxx::deallocate(block);
}
*/