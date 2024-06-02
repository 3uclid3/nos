#include <kernel/memory/physical_memory.hpp>

#include <string.h>

#include <kernel/boot/limine.hpp>
#include <kernel/log.hpp>
#include <nxx/algorithm/max.hpp>
#include <nxx/container/span.hpp>
#include <nxx/memory/alignment.hpp>

namespace nos {

void physical_memory::bitmap::init(span<u8_t> data)
{
    _data = data;

    memset(_data.data(), 0xFF, _data.size());
}

void physical_memory::bitmap::set(size_t index)
{
    _data[index / 8] |= 1 << (index % 8);
}

void physical_memory::bitmap::clear(size_t index)
{
    _data[index / 8] &= ~(1 << (index % 8));
}

bool physical_memory::bitmap::test(size_t index)
{
    return _data[index / 8] & (1 << (index % 8));
}

void physical_memory::init()
{
    auto& memmap_request = limine::get_memmap_request();
    auto& hhdm_request = limine::get_hhdm_request();

    NOS_ASSERT(memmap_request.response != nullptr);
    NOS_ASSERT(hhdm_request.response != nullptr);

    _hhdm_offset = hhdm_request.response->offset;

    limine_memmap_response& response = *memmap_request.response;

    span<limine_memmap_entry*> entries{response.entries, response.entry_count};
    init_bounds(entries);
    init_bitmap_buffer(entries);
    init_bitmap(entries);
}

void physical_memory::init_bounds(span<limine_memmap_entry*> entries)
{
    for (const limine_memmap_entry* entry : entries)
    {
        const uintptr_t entry_max_address = entry->base + entry->length;
        _max_base_address = max(_max_base_address, entry_max_address);

        switch (entry->type)
        {
        case LIMINE_MEMMAP_USABLE:
            _usable_size += entry->length;
            _max_usable_base_address = max(_max_usable_base_address, entry_max_address);
            break;

        case LIMINE_MEMMAP_ACPI_RECLAIMABLE:
        case LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE:
        case LIMINE_MEMMAP_KERNEL_AND_MODULES:
            _used_size += entry->length;
            break;

        default:
            continue;
        }

        _total_size += entry->length;
    }

    log::trace("pmm: total_size = {}, used_size = {}, usable_size = {}, max_address = 0x{:X}, max_usable_address = 0x{:X}",
               _total_size,
               _used_size,
               _usable_size,
               _max_base_address,
               _max_usable_base_address);
}

void physical_memory::init_bitmap_buffer(span<limine_memmap_entry*> entries)
{
    const size_t bitmap_size = align_up(_max_usable_base_address / page_size / 8, page_size);
    for (limine_memmap_entry* entry : entries)
    {
        if (entry->type != LIMINE_MEMMAP_USABLE)
        {
            continue;
        }

        if (entry->length >= bitmap_size)
        {
            span<u8_t> bitmap_buffer{reinterpret_cast<u8_t*>(entry->base + _hhdm_offset), bitmap_size};
            _bitmap.init(bitmap_buffer);

            entry->base += bitmap_size;
            entry->length -= bitmap_size;

            _used_size += bitmap_size;

            log::trace("pmm: bitmap_buffer = 0x{:X}, bitmap_size = {}", bitmap_buffer.data(), bitmap_buffer.size());
            break;
        }
    }
}

void physical_memory::init_bitmap(span<limine_memmap_entry*> entries)
{
    for (const limine_memmap_entry* entry : entries)
    {
        if (entry->type != LIMINE_MEMMAP_USABLE)
        {
            continue;
        }

        const size_t start_page = entry->base / page_size;
        const size_t end_page = (entry->base + entry->length) / page_size;

        for (size_t page = start_page; page < end_page; ++page)
        {
            _bitmap.clear(page);
        }
    }
}

} // namespace nos
