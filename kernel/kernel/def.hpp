#pragma once

#include <nxx/def.hpp>

#define NOS_ASSERT(condition, ...) NXX_ASSSERT(condition, __VA__ARGS__)
#define NOS_UNUSED(var) NXX_UNUSED(var)
#define NOS_UNREACHABLE() NXX_UNREACHABLE()
#define NOS_INCLUDE_KERNEL_ARCH(file) <kernel/arch/NOS_ARCH/file>

namespace nos {

using nullptr_t = nxx::nullptr_t;

using intptr_t = nxx::intptr_t;
using uintptr_t = nxx::uintptr_t;
using ptrdiff_t = nxx::ptrdiff_t;

using s8_t = nxx::s8_t;
using s16_t = nxx::s16_t;
using s32_t = nxx::s32_t;
using s64_t = nxx::s64_t;

using u8_t = nxx::u8_t;
using u16_t = nxx::u16_t;
using u32_t = nxx::u32_t;
using u64_t = nxx::u64_t;

using f32_t = nxx::f32_t;
using f64_t = nxx::f64_t;

using size_t = nxx::size_t;

inline constexpr size_t bits_per_byte{nxx::bits_per_byte};

} // namespace nxx