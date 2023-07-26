#include <ncxx/basic-types.hpp>

namespace NOS {

static_assert(sizeof(u8_t) == 1);
static_assert(sizeof(s8_t) == 1);

static_assert(sizeof(u16_t) == 2);
static_assert(sizeof(s16_t) == 2);

static_assert(sizeof(u32_t) == 4);
static_assert(sizeof(s32_t) == 4);

static_assert(sizeof(u64_t) == 8);
static_assert(sizeof(s64_t) == 8);

static_assert(sizeof(f32_t) == 4);
static_assert(sizeof(f64_t) == 8);
static_assert(sizeof(f128_t) == 16);

} // namespace NOS