#pragma once

#include <nxx/def.hpp>

#define NOS_ASSERT(...) NXX_ASSERT(__VA_ARGS__)
#define NOS_UNUSED(var) NXX_UNUSED(var)
#define NOS_UNREACHABLE() NXX_UNREACHABLE()
#define NOS_PACKED __attribute__((packed))

#define NOS_INCLUDE_KERNEL_ARCH(file) <kernel/arch/NOS_ARCH/file>

namespace nos {

// import nxx
using namespace nxx;

// declare namespace for arch
namespace NOS_ARCH {
}

// import NOS_ARCH into current_arch
namespace current_arch {
using namespace NOS_ARCH;
} // namespace current_arch

} // namespace nos
