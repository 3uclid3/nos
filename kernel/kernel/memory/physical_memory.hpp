#pragma once

#include <kernel/def.hpp>
#include <nxx/container/span.hpp>

struct limine_memmap_entry;

namespace nos {

class physical_memory
{
public:
    static constexpr size_t page_size = 0x1000;
    
public:
    void init();

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

    private:
        span<u8_t> _data;
    };

    bitmap _bitmap;

    size_t _total_size{0};
    size_t _used_size{0};
    size_t _usable_size{0};
    
    uintptr_t _max_base_address{0};
    uintptr_t _max_usable_base_address{0};

    uintptr_t _hhdm_offset{0};
};

} // namespace nos
