#include <cxx/cxa.hpp>

#include <cassert>

#include <kdef.hpp>
#include <lib/log.hpp>

BEGIN_C_DECLS

static constexpr size_t __cxa_atexit_entries_capacity = 128;

using __cxa_guard = int;

struct __cxa_atexit_entry
{
    void (*destructor_func)(void*){nullptr};
    void* object_ptr{nullptr};
    void* dso_handle{nullptr};
};

__cxa_atexit_entry __atexit_entries[__cxa_atexit_entries_capacity];
size_t __atexit_entries_count{0};

void* __dso_handle{nullptr};

int __cxa_atexit(void (*destructor_func)(void*), void* object_ptr, void* dso_handle)
{
    if (__atexit_entries_count >= __cxa_atexit_entries_capacity)
    {
        return -1;
    }

    __atexit_entries[__atexit_entries_count].destructor_func = destructor_func;
    __atexit_entries[__atexit_entries_count].object_ptr = object_ptr;
    __atexit_entries[__atexit_entries_count].dso_handle = dso_handle;

    ++__atexit_entries_count;

    return 0;
}

void __cxa_finalize(void* dso_handle)
{
    if (dso_handle == nullptr)
    {
        for (size_t i = __atexit_entries_count; i--;)
        {
            if (__atexit_entries[i].destructor_func)
            {
                (*__atexit_entries[i].destructor_func)(__atexit_entries[i].object_ptr);
            }
        }

        __atexit_entries_count = 0;
    }
    else
    {
        for (size_t i = __atexit_entries_count; i--;)
        {
            __cxa_atexit_entry& entry = __atexit_entries[i];

            if (entry.dso_handle == dso_handle)
            {
                (*entry.destructor_func)(entry.object_ptr);

                // Ensure we do not call this entry again.
                // We don't care about maintaining the __atexit_entries_count.
                // It's not worth moving all the entries
                entry = {};
            };
        };
    }
}

void __cxa_pure_virtual()
{
    assert(false);
}

int __cxa_guard_acquire(__cxa_guard* g)
{
    return !*(reinterpret_cast<volatile uint8_t*>(g));
}

void __cxa_guard_release(__cxa_guard* g)
{
    *(reinterpret_cast<volatile uint8_t*>(g)) = 1;
}

void __cxa_guard_abort(__cxa_guard* g)
{
    // Typically used if constructor throws an exception (optional for bare-metal)
    // Reset the guard to 0 to indicate initialization failed.
    *(reinterpret_cast<volatile uint8_t*>(g)) = 0;
}

END_C_DECLS

namespace nos::cxa {

C_DECL void (*__init_array_start[])();
C_DECL void (*__init_array_end[])();

void init()
{
    log::trace("cxa: init");

    for (auto ctor = __init_array_start; ctor < __init_array_end; ++ctor)
    {
        (*ctor)();
    }
}

} // namespace nos::cxa
