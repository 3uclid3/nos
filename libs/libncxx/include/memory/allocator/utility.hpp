#pragma once

#include <base_types.hpp>
#include <type_traits/integral_constant.hpp>

namespace nos::memory::allocator {

constexpr size_t round_to_aligned(size_t size, alignment_t align = default_alignment);

} // namespace nos::memory::allocator
