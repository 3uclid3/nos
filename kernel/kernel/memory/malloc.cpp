#include <ncxx/basic-types.hpp>

extern "C" {

void* malloc(size_t)
{
    return nullptr;
}

void* realloc(void*, size_t)
{
    return nullptr;
}

void free(void*)
{
}

} //
