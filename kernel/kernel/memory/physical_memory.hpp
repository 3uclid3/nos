#pragma once

#include <kernel/def.hpp>
#include <nxx/container/span.hpp>

struct limine_memmap_entry;

namespace nos {

constexpr size_t bytes_to_pages(size_t bytes);
constexpr size_t pages_to_bytes(size_t bytes);

class physical_memory
{
public:
    static constexpr size_t page_size = 0x1000;

    static inline uintptr_t tohh(uintptr_t physical_address)
    {
        return physical_address + _hhdm_offset;
    }

    static inline uintptr_t toph(uintptr_t high_half_address)
    {
        return high_half_address - _hhdm_offset;
    }

public:
    void init();

    void* allocate_pages(size_t count = 1);
    void deallocate_pages(void* ptr, size_t count = 1);

    template<typename T>
    T* allocate_pages(size_t count = 1);

    size_t total_size() const { return _total_size; }
    size_t used_size() const { return _used_size; }
    size_t usable_size() const { return _usable_size; }

private:
    void init_bounds(span<limine_memmap_entry*> entries);
    void init_bitmap_buffer(span<limine_memmap_entry*> entries);
    void init_bitmap(span<limine_memmap_entry*> entries);

private:
    class bitmap
    {
    public:
        void init(span<u8_t> data);

        void set(size_t index);
        void clear(size_t index);
        bool test(size_t index);

        size_t size() const { return _data.size() * 8; }

    private:
        span<u8_t> _data;
    };

    bitmap _bitmap;

    size_t _total_size{0};
    size_t _used_size{0};
    size_t _usable_size{0};

    uintptr_t _max_base_address{0};
    uintptr_t _max_usable_base_address{0};

    inline static uintptr_t _hhdm_offset{0};
};

constexpr size_t bytes_to_pages(size_t bytes)
{
    return (bytes + physical_memory::page_size - 1) / physical_memory::page_size;
}

constexpr size_t pages_to_bytes(size_t bytes)
{
    return bytes * physical_memory::page_size;
}

template<typename T>
T* physical_memory::allocate_pages(size_t count)
{
    return reinterpret_cast<T*>(allocate_pages(count));
}

} // namespace nos
