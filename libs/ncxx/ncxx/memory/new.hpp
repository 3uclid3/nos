#pragma once

#ifdef NOS_NATIVE

#include <new>

#else

#include <ncxx/basic-types.hpp>

inline void* operator new(size_t, void* p) noexcept
{
    return p;
}

inline void* operator new[](size_t, void* p) noexcept
{
    return p;
}

inline void operator delete(void*, void*)
{
}

inline void operator delete[](void*, void*)
{
}

#endif
