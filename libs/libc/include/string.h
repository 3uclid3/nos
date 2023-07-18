#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int memcmp(const void* ptr1, const void* ptr2, size_t size);
void* memcpy(void* destination, const void* source, size_t size);
void* memmove(void* destination, const void* source, size_t size);
void* memset(void* ptr, int c, size_t size);

#ifdef __cplusplus
}
#endif
