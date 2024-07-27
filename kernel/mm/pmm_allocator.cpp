#include <mm/pmm_allocator.hpp>

#include <mm/pmm.hpp>

namespace nos {

bool pmm_allocator::owns(const coal::memory_block& block) const
{
    // TODO stack
    return true;
}

coal::memory_block pmm_allocator::allocate(size_t size)
{
    const auto page_count = bytes_to_pages(size);

    uintptr_t page_intptr = pmm::tohh(reinterpret_cast<uintptr_t>(_pmm->allocate_pages(page_count)));
    void* page_ptr = reinterpret_cast<void*>(page_intptr);

    return coal::memory_block{page_ptr, size};
}

bool pmm_allocator::reallocate([[maybe_unused]] coal::memory_block& block, [[maybe_unused]] std::size_t new_size)
{
    deallocate(block);
    block = allocate(new_size);
    return block;
}

void pmm_allocator::deallocate(coal::memory_block& block)
{
    const auto page_count = bytes_to_pages(block.size);

    uintptr_t page_intptr = pmm::toph(reinterpret_cast<uintptr_t>(block.ptr));
    void* page_ptr = reinterpret_cast<void*>(page_intptr);

    _pmm->deallocate_pages(page_ptr, page_count);
}

} // namespace nos
