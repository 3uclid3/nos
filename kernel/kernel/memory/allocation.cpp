#include <kernel/memory/allocation.hpp>

#include <ncxx/memory/allocator/stack-allocator.hpp>

namespace NOS::Memory {

namespace Details {

using GlobalAllocator = Memory::StackAllocator<8196 * 1>;

GlobalAllocator globalAllocator;

} // namespace Details

Block allocate(size_t size)
{
    return Details::globalAllocator.allocate(size);
}

Block reallocate(Block block, size_t size)
{
    return Details::globalAllocator.reallocate(block, size);
}

void deallocate(Block block)
{
    Details::globalAllocator.deallocate(block);
}

} // namespace NOS::Memory