#pragma once

#include <base_types.hpp>

namespace nos::memory {

struct block
{
    void* pointer;
    size_t size;
};

inline constexpr block null_block{nullptr, 0};

} // namespace nos::memory
