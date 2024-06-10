#include <kernel/memory/allocate.hpp>

#include <kernel/memory/physical_memory.hpp>
#include <kernel/memory/physical_memory_allocator.hpp>
#include <nxx/memory/allocator/affix/memory_corruption_detector.hpp>
#include <nxx/memory/allocator/affix_allocator.hpp>
#include <nxx/memory/allocator/free_list_allocator.hpp>
#include <nxx/memory/allocator/free_list_strategy/best_fit_free_list_strategy.hpp>
#include <nxx/memory/allocator/free_list_strategy/limited_size_free_list_strategy.hpp>
#include <nxx/memory/allocator/prefixed_size_allocator.hpp>
#include <nxx/memory/allocator/segregator_allocator.hpp>
#include <nxx/memory/allocator/slab_allocator.hpp>
#include <nxx/memory/allocator/stack_allocator.hpp>

namespace nxx {

namespace details {

#if NOS_MEMORY_CORRUPTION_DETECTOR_ENABLED

using corruption_detector = memory_corruption_detector<u32_t, 0xDEADDEAD>;

constexpr size_t size(size_t s)
{
    return sizeof(corruption_detector) + s;
}

using heap_allocator_t = affix_allocator<
    segregator_allocator<
        slab_allocator<nos::physical_memory_allocator, nos::physical_memory::page_size * 2, size(8), size(16), size(32), size(64), size(128), size(512), size(1024)>,
        free_list_allocator<prefixed_size_allocator<nos::physical_memory_allocator>, limited_size_free_list_strategy<best_fit_free_list_strategy, 64>>,
        1024>,
    corruption_detector,
    corruption_detector>;

#else

using heap_allocator_t = segregator_allocator<
        slab_allocator<nos::physical_memory_allocator, nos::physical_memory::page_size, 8, 16, 32, 64, 128, 512, 1024>,
        free_list_allocator<prefixed_size_allocator<nos::physical_memory_allocator>, limited_size_free_list_strategy<best_fit_free_list_strategy, 64>>,
        1024>>;

#endif

heap_allocator_t heap_allocator{};

} // namespace details

memory_block allocate(size_t size)
{
    return details::heap_allocator.allocate(size);
}

bool expand_allocate(memory_block& block, size_t delta)
{
    return details::heap_allocator.expand(block, delta);
}

bool reallocate(memory_block& block, size_t new_size)
{
    return details::heap_allocator.reallocate(block, new_size);
}

void deallocate(memory_block& block)
{
    details::heap_allocator.deallocate(block);
}

} // namespace nxx