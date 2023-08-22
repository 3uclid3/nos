#include <ncxx/memory/allocator/system-allocator.hpp>

#include <ncxx/memory/allocation.hpp>
#include <ncxx/memory/block.hpp>
#include <ncxx/preprocessor/unused.hpp>

namespace NOS::Memory {

bool SystemAllocator::owns(ConstBlock block) const
{
    NOS_UNUSED(block);
    return true;
}

Block SystemAllocator::allocate(size_t size)
{
    return Memory::allocate(size);
}

void SystemAllocator::deallocate(Block block)
{
    return Memory::deallocate(block);
}

void SystemAllocator::deallocateAll()
{
}

Block SystemAllocator::expand(Block block, size_t size)
{
    NOS_UNUSED(block);
    NOS_UNUSED(size);
    return nullblk;
}

Block SystemAllocator::reallocate(Block block, size_t size)
{
    return Memory::reallocate(block, size);
}

} // namespace NOS::Memory
