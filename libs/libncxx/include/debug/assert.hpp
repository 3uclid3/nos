#pragma once 

#define N_ASSERT(condition, ...) \
do { \
 if (!(condition)) __builtin_trap(); \
} while(false)
