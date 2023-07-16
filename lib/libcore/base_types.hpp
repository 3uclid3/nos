#pragma once

#include <stddef.h>
#include <stdint.h>

namespace nos {

using nullptr_t = decltype(nullptr);

using ::intmax_t;
using ::intptr_t;

using ::uintmax_t;
using ::uintptr_t;

using s8_t = ::int8_t;
using s16_t = ::int16_t;
using s32_t = ::int32_t;
using s64_t = ::int64_t;

using u8_t = ::uint8_t;
using u16_t = ::uint16_t;
using u32_t = ::uint32_t;
using u64_t = ::uint64_t;

using f32_t = float;
using f64_t = double;

using size_t = ::size_t;

enum class byte : u8_t
{
    zero = 0x00,

    null_terminated = '\0'
};

} // namespace nos
