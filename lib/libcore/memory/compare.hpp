#pragma once

#include <base_types.hpp>

namespace nos::memory {

enum class compare_result
{
    lesser = -1,
    equals = 0,
    greater = 1
};

[[nodiscard]] compare_result compare(const void* lhs, const void* rhs, size_t size);

} // namespace nos::memory
