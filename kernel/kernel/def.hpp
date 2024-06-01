#pragma once

#include <kernel_config.hpp>
#include <nxx/def.hpp>

#define NOS_ASSERT(...) NXX_ASSERT(__VA_ARGS__)
#define NOS_UNUSED(var) NXX_UNUSED(var)
#define NOS_UNREACHABLE() NXX_UNREACHABLE()
#define NOS_PACKED __attribute__((packed))

namespace nos {

// import nxx
using namespace nxx;

} // namespace nos
