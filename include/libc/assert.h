#pragma once

#include <hedley.h>

HEDLEY_BEGIN_C_DECLS

HEDLEY_NO_RETURN void assert_fail(const char* message, const char* file, int line, const char* func);

#define _ASSERT_MSG(x, msg) (!(x) ? assert_fail((msg), __FILE__, __LINE__, __PRETTY_FUNCTION__) : (void)((char*)(msg)))
#define _ASSERT_NOMSG(x) (!(x) ? assert_fail("Assertion failed: " #x, __FILE__, __LINE__, __PRETTY_FUNCTION__) : (void)(0))
#define _GET_ASSERT_MACRO(_1, _2, NAME, ...) NAME

#define assert(...) _GET_ASSERT_MACRO(__VA_ARGS__, _ASSERT_MSG, _ASSERT_NOMSG)(__VA_ARGS__)

HEDLEY_END_C_DECLS
