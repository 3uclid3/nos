#pragma once

#include <cstdint>

#include <coal/affix/memory_corruption_detector.hpp>
#include <coal/free_list_allocator.hpp>
#include <coal/free_list_strategy/best_fit.hpp>
#include <coal/free_list_strategy/limited_size.hpp>
#include <coal/prefixed_size_allocator.hpp>
#include <coal/proxy_allocator.hpp>
#include <coal/segregator_allocator.hpp>
#include <coal/slab_allocator.hpp>

#include <mm/hh_pmm_allocator.hpp>
#include <mm/pmm.hpp>
#include <mm/sizes.hpp>

#ifndef NOS_MEMORY_CORRUPTION_DETECTOR_ENABLED
#ifdef NDEBUG
#define NOS_MEMORY_CORRUPTION_DETECTOR_ENABLED 0
#else
#define NOS_MEMORY_CORRUPTION_DETECTOR_ENABLED 1
#endif
#endif

namespace nos {

using heap_allocator_t =
#if NOS_MEMORY_CORRUPTION_DETECTOR_ENABLED
    coal::affix_allocator<
#endif
        coal::segregator_allocator<coal::slab_allocator<hh_pmm_allocator, page_size * 2, 8, 16, 32, 64, 128, 192, 288, 448, 672, 1024>,
                                   coal::free_list_allocator<coal::prefixed_size_allocator<hh_pmm_allocator>, coal::free_list_strategy::limited_size<coal::free_list_strategy::best_fit, 64>>,
                                   1024>
#if NOS_MEMORY_CORRUPTION_DETECTOR_ENABLED
        ,
        coal::memory_corruption_detector<std::uint32_t, 0xDEADDEAD, 1>,
        coal::memory_corruption_detector<std::uint32_t, 0xDEADDEAD, 1>>
#endif
    ;

using kmalloc_heap_allocator_t = coal::prefixed_size_allocator<coal::proxy_allocator<heap_allocator_t>>;

} // namespace nos
