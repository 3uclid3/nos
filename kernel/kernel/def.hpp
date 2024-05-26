#pragma once

#include <nxx/def.hpp>

#define NOS_ASSERT(condition, ...) NXX_ASSERT(condition, __VA_ARGS__)
#define NOS_UNUSED(var) NXX_UNUSED(var)
#define NOS_UNREACHABLE() NXX_UNREACHABLE()
#define NOS_INCLUDE_KERNEL_ARCH(file) <kernel/arch/NOS_ARCH/file>

namespace nos {
using namespace nxx;
} // namespace nos
