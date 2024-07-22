#include <assert.h>

void assert_fail(const char* message, const char* file, int line, const char* func)
{
    __builtin_trap();
}
