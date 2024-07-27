#include <new>

#include <mm/heap.hpp>

void* operator new(std::size_t size)
{
    return nos::heap::get_active()->get_allocator().allocate(size).ptr;
}

void* operator new(std::size_t size, std::align_val_t)
{
    return nos::heap::get_active()->get_allocator().allocate(size).ptr;
}

void* operator new[](std::size_t size)
{
    return nos::heap::get_active()->get_allocator().allocate(size).ptr;
}

void* operator new[](std::size_t size, std::align_val_t)
{
    return nos::heap::get_active()->get_allocator().allocate(size).ptr;
}

void operator delete(void*) noexcept
{
    assert(false);
}

void operator delete(void*, std::align_val_t) noexcept
{
    assert(false);
}

void operator delete(void* ptr, std::size_t size) noexcept
{
    coal::memory_block block(ptr, size);
    nos::heap::get_active()->get_allocator().deallocate(block);
    assert(!block);
}

void operator delete(void* ptr, std::size_t size, std::align_val_t) noexcept
{
    coal::memory_block block(ptr, size);
    nos::heap::get_active()->get_allocator().deallocate(block);
    assert(!block);
}

void operator delete[](void*) noexcept
{
    assert(false);
}

void operator delete[](void*, std::align_val_t) noexcept
{
    assert(false);
}

void operator delete[](void* ptr, std::size_t size) noexcept
{
    coal::memory_block block(ptr, size);
    nos::heap::get_active()->get_allocator().deallocate(block);
    assert(!block);
}

void operator delete[](void* ptr, std::size_t size, std::align_val_t) noexcept
{
    coal::memory_block block(ptr, size);
    nos::heap::get_active()->get_allocator().deallocate(block);
    assert(!block);
}
