#pragma once

#include <base-types.hpp>

namespace nos::memory {

constexpr size_t roundToAlignment(size_t size, alignment_t align)
{
    const size_t alignAsSizeT = static_cast<size_t>(align);
    return size + ((size % alignAsSizeT) == 0 ? 0 : alignAsSizeT - (size % alignAsSizeT));
}

} // namespace nos::memory
