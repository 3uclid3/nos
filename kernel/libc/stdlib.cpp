#include <stdlib.h>

#include <assert.h>

#include <coal/prefixed_size_allocator.hpp>
#include <coal/proxy_allocator.hpp>

#include <mm/heap.hpp>

namespace nos {

using kmalloc_allocator_t = coal::prefixed_size_allocator<coal::proxy_allocator<heap_allocator_t>>;

kmalloc_allocator_t& get_kmalloc_allocator()
{
    assert(heap::get_active_allocator());

    static kmalloc_allocator_t kmalloc_allocator = []() {
        kmalloc_allocator_t allocator;
        allocator.get_allocator().set_allocator(heap::get_active_allocator());
        return allocator;
    }();

    return kmalloc_allocator;
}

} // namespace nos

BEGIN_C_DECLS

void* malloc(size_t size)
{
    return nos::get_kmalloc_allocator().allocate(size).ptr;
}

void* calloc(size_t num, size_t size)
{
    assert(false);
    return nullptr;
}

void* realloc(void* oldptr, size_t size)
{
    coal::memory_block block(oldptr, 0);
    nos::get_kmalloc_allocator().reallocate(block, size);
    return block.ptr;
}

void free(void* ptr)
{
    coal::memory_block block(ptr, 0);
    nos::get_kmalloc_allocator().deallocate(block);
}

int atoi(const char* str)
{
    assert(false);
    return 0;
}

long atol(const char* str)
{
    assert(false);
    return 0;
}

long long atoll(const char* str)
{
    assert(false);
    return 0;
}

long strtol(const char* str, char** str_end, int base)
{
    assert(false);
    return 0;
}

long long strtoll(const char* str, char** str_end, int base)
{
    assert(false);
    return 0;
}

unsigned long strtoul(const char* str, char** str_end, int base)
{
    assert(false);
    return 0;
}

unsigned long long strtoull(const char* str, char** str_end, int base)
{
    assert(false);
    return 0;
}

END_C_DECLS
