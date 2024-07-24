#include <assert.h>

#include <lib/format.hpp>
#include <lib/panic.hpp>

HEDLEY_BEGIN_C_DECLS

void assert_fail(const char* message, const char* file, int line, const char* func)
{
    nos::panic(message, file, line, func);
}

HEDLEY_END_C_DECLS
