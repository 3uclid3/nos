#include <kernel/cxx/memory.hpp>

#include <kernel/def.hpp>

void operator delete(void*, unsigned long)
{
    NOS_ASSERT(false);
}
