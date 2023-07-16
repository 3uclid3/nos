#pragma once

#include <base_types.hpp>

namespace nos::memory {
    
[[nodiscard]] void* copy(void* destination, const void* source, size_t size);

} // namespace nos::memory