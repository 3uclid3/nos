#pragma once

#ifndef NOS_LIBC_API_USE_PREFIX

#define NOS_LIBC(func_name) func_name 

#define NOS_LIBC_INCLUDE_STRING_H <string.h>

#else

#define NOS_LIBC(func_name) nos_##func_name 

#define NOS_LIBC_INCLUDE_STRING_H <nos_string.h>

#endif
