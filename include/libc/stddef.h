#pragma once

typedef __SIZE_TYPE__ size_t;
typedef __PTRDIFF_TYPE__ ptrdiff_t;

typedef long ssize_t;
typedef double max_align_t;

#undef NULL

#ifdef __cplusplus

#define NULL __null

#define BEGIN_C_DECLS extern "C" {
#define END_C_DECLS }
#define C_DECL extern "C"

#else

#define NULL ((void*)0)

#define BEGIN_C_DECLS
#define END_C_DECLS
#define C_DECL

typedef __WCHAR_TYPE__ wchar_t;

#endif

#define offsetof(type, member) __builtin_offsetof(type, member)
