#pragma once

#define NOS_ASSERT(condition, ...) \
    do { \
        if (!(condition)) __builtin_trap(); \
    } while (false)
