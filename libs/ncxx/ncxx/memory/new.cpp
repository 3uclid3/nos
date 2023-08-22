#include <ncxx/memory/new.hpp>

#ifndef NOS_NATIVE

#include <ncxx/debug/assert.hpp>
#include <ncxx/memory/allocation.hpp>
#include <ncxx/memory/block.hpp>

void* operator new(NOS::size_t size)
{
    NOS::Memory::Block block = NOS::Memory::allocate(size);
    NOS_ASSERT(block.pointer != nullptr);
    return block.pointer;
}

void* operator new[](NOS::size_t size)
{
    NOS::Memory::Block block = NOS::Memory::allocate(size);
    NOS_ASSERT(block.pointer != nullptr);
    return block.pointer;
}

void operator delete(void* ptr) noexcept
{
    // TODO Size
    NOS::Memory::Block block{.pointer = ptr, .size = 0};
    NOS::Memory::deallocate(block);
}

void operator delete[](void* ptr) noexcept
{
    // TODO Size
    NOS::Memory::Block block{.pointer = ptr, .size = 0};
    NOS::Memory::deallocate(block);
}

void operator delete(void* ptr, NOS::size_t size) noexcept
{
    NOS::Memory::Block block{.pointer = ptr, .size = size};
    NOS::Memory::deallocate(block);
}

void operator delete[](void* ptr, NOS::size_t size) noexcept
{
    NOS::Memory::Block block{.pointer = ptr, .size = size};
    NOS::Memory::deallocate(block);
}

#endif
