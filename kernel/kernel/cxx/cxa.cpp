#include <kernel/cxx/cxa.hpp>

#include <kernel/def.hpp>
#include <kernel/log.hpp>

extern "C" {

static constexpr size_t at_exit_maximum_entries_capacity = 128;

using __guard = int;

using atexit_func_t = void (*)(void*);

struct atexit_func_entry
{
    atexit_func_t func{nullptr};
    void* object_ptr{nullptr};
    void* dso_handle{nullptr};
};

atexit_func_entry __atexit_funcs[at_exit_maximum_entries_capacity];
size_t __atexit_func_count{0};
void* __dso_handle{nullptr};

int __cxa_atexit(atexit_func_t func, void* object_ptr, void* dso_handle)
{
    if (__atexit_func_count >= at_exit_maximum_entries_capacity)
    {
        return -1;
    }

    __atexit_funcs[__atexit_func_count].func = func;
    __atexit_funcs[__atexit_func_count].object_ptr = object_ptr;
    __atexit_funcs[__atexit_func_count].dso_handle = dso_handle;

    ++__atexit_func_count;

    return 0;
}

void __cxa_finalize(void* dso_handle)
{
    if (dso_handle == nullptr)
    {
        for (size_t i = __atexit_func_count; i--;)
        {
            if (__atexit_funcs[i].func)
            {
                (*__atexit_funcs[i].func)(__atexit_funcs[i].object_ptr);
            }
        }

        __atexit_func_count = 0;
    }
    else
    {
        for (size_t i = __atexit_func_count; i--;)
        {
            atexit_func_entry& entry = __atexit_funcs[i];

            if (entry.dso_handle == dso_handle)
            {
                (*entry.func)(entry.object_ptr);

                // Ensure we do not call this entry again.
                // We don't care about maintaining the __atexit_func_count.
                // It's not worth moving all the entries
                entry = {};
            };
        };
    }
}

void __cxa_pure_virtual()
{
    NOS_ASSERT(false);
}

int __cxa_guard_acquire(__guard* g)
{
    return !*(reinterpret_cast<volatile uint8_t*>(g));
}

void __cxa_guard_release(__guard* g)
{
    *(reinterpret_cast<volatile uint8_t*>(g)) = 1;
}

void __cxa_guard_abort(__guard* g)
{
    // Typically used if constructor throws an exception (optional for bare-metal)
    // Reset the guard to 0 to indicate initialization failed.
    *(reinterpret_cast<volatile uint8_t*>(g)) = 0;
}

} // extern "C"

namespace nos::cxa {

extern "C" void (*__init_array_start[])();
extern "C" void (*__init_array_end[])();

void init()
{
    log::trace("cxa: init");
    for (auto ctor = __init_array_start; ctor < __init_array_end; ++ctor)
    {
        (*ctor)();
    }
}

} // namespace nos::cxa