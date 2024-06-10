#include <kernel/memory/physical_memory_allocator.hpp>

#include <kernel/memory/physical_memory.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nos {

bool physical_memory_allocator::owns(const memory_block& block) const
{
    // is stack?
    return block;
}

memory_block physical_memory_allocator::allocate(size_t size)
{
    const auto page_count = bytes_to_pages(size);

    uintptr_t page_intptr = physical_memory::tohh(reinterpret_cast<uintptr_t>(_physical_memory->allocate_pages(page_count)));
    void* page_ptr = reinterpret_cast<void*>(page_intptr);

    return memory_block{page_ptr, size};
}

void physical_memory_allocator::deallocate(memory_block& block)
{
    const auto page_count = bytes_to_pages(block.size);

    uintptr_t page_intptr = physical_memory::toph(reinterpret_cast<uintptr_t>(block.ptr));
    void* page_ptr = reinterpret_cast<void*>(page_intptr);

    _physical_memory->deallocate_pages(page_ptr, page_count);
}

} // namespace nos
