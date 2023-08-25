#pragma once

#ifdef NOS_NATIVE

#include <new>

#else

#include <ncxx/basic-types.hpp>
#include <ncxx/preprocessor/unused.hpp>

[[nodiscard]] void* operator new(NOS::size_t size);
[[nodiscard]] void* operator new[](NOS::size_t size);
[[nodiscard]] void* operator new(NOS::size_t size, void* ptr);
[[nodiscard]] void* operator new[](NOS::size_t size, void* ptr);

void operator delete(void* ptr) noexcept;
void operator delete[](void* ptr) noexcept;
void operator delete(void* ptr, NOS::size_t size) noexcept;
void operator delete[](void* ptr, NOS::size_t size) noexcept;
void operator delete(void* ptr, void* place) noexcept;
void operator delete[](void* ptr, void* place) noexcept;

[[nodiscard]] inline void* operator new(NOS::size_t size, void* ptr)
{
    NOS_UNUSED(size);
    return ptr;
}

[[nodiscard]] inline void* operator new[](NOS::size_t size, void* ptr)
{
    NOS_UNUSED(size);
    return ptr;
}

inline void operator delete(void* ptr, void* place) noexcept
{
    NOS_UNUSED(ptr);
    NOS_UNUSED(place);
}

inline void operator delete[](void* ptr, void* place) noexcept
{
    NOS_UNUSED(ptr);
    NOS_UNUSED(place);
}

#endif
