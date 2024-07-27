#include <mm/pmm.hpp>

#include <cassert>
#include <cstring>

#include <coal/alignment.hpp>

#include <init/bootloader.hpp>
#include <lib/log.hpp>
#include <lib/managed_object.hpp>
#include <mm/heap_allocator.hpp>
#include <mm/sizes.hpp>

namespace nos {

void pmm::bitmap::init(std::span<std::uint8_t> data)
{
    _data = data;

    std::memset(_data.data(), 0xFF, _data.size());
}

void pmm::bitmap::set(std::size_t index)
{
    _data[index / 8] |= 1 << (index % 8);
}

void pmm::bitmap::clear(std::size_t index)
{
    _data[index / 8] &= ~(1 << (index % 8));
}

bool pmm::bitmap::test(std::size_t index)
{
    return _data[index / 8] & (1 << (index % 8));
}

void pmm::init()
{
    auto& memmap_request = limine::get_memmap_request();
    auto& hhdm_request = limine::get_hhdm_request();

    assert(memmap_request.response != nullptr);
    assert(hhdm_request.response != nullptr);

    _hhdm_offset = hhdm_request.response->offset;

    limine_memmap_response& response = *memmap_request.response;

    std::span<limine_memmap_entry*> entries{response.entries, response.entry_count};
    init_bounds(entries);
    init_bitmap_buffer(entries);
    init_bitmap(entries);
}

void* pmm::allocate_pages(std::size_t count)
{
    for (std::size_t page = 0; page < _bitmap.size(); ++page)
    {
        if (_bitmap.test(page))
        {
            continue;
        }

        bool found = true;
        std::size_t i = 1;
        for (; i < count; ++i)
        {
            if (_bitmap.test(page + i))
            {
                found = false;
                break;
            }
        }

        if (!found)
        {
            // skip checked pages
            page = page + i;
            continue;
        }

        for (i = 0; i < count; ++i)
        {
            _bitmap.set(page + i);
        }

        _used_size += count * page_size;

        return reinterpret_cast<void*>(page * page_size);
    }

    return nullptr;
}

void pmm::deallocate_pages(void* ptr, std::size_t count)
{
    if (ptr == nullptr)
    {
        return;
    }

    const std::size_t page = reinterpret_cast<uintptr_t>(ptr) / page_size;

    for (std::size_t i = page; i < page + count; ++i)
    {
        _bitmap.clear(i);
    }

    _used_size -= count * page_size;
}

void pmm::init_bounds(std::span<limine_memmap_entry*> entries)
{
    for (const limine_memmap_entry* entry : entries)
    {
        const uintptr_t entry_max_address = entry->base + entry->length;
        _max_base_address = std::max(_max_base_address, entry_max_address);

        switch (entry->type)
        {
        case LIMINE_MEMMAP_USABLE:
            _usable_size += entry->length;
            _max_usable_base_address = std::max(_max_usable_base_address, entry_max_address);
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

    log::trace("pmm: total_size = {}mb, used_size = {}mb, usable_size = {}mb, max_base_address = 0x{:X}, max_usable_base_address = 0x{:X}",
               bytes_to_megabytes(_total_size),
               bytes_to_megabytes(_used_size),
               bytes_to_megabytes(_usable_size),
               _max_base_address,
               _max_usable_base_address);
}

void pmm::init_bitmap_buffer(std::span<limine_memmap_entry*> entries)
{
    const std::size_t bitmap_size = coal::align_up(_max_usable_base_address / page_size / 8, page_size);
    for (limine_memmap_entry* entry : entries)
    {
        if (entry->type != LIMINE_MEMMAP_USABLE)
        {
            continue;
        }

        if (entry->length >= bitmap_size)
        {
            std::span<std::uint8_t> bitmap_buffer{reinterpret_cast<std::uint8_t*>(tohh(entry->base)), bitmap_size};
            _bitmap.init(bitmap_buffer);

            entry->base += bitmap_size;
            entry->length -= bitmap_size;

            _used_size += bitmap_size;

            log::trace("pmm: bitmap_buffer = 0x{:X}, bitmap_size = {}kb", entry->base, bytes_to_kilobytes(bitmap_buffer.size()));
            break;
        }
    }
}

void pmm::init_bitmap(std::span<limine_memmap_entry*> entries)
{
    for (const limine_memmap_entry* entry : entries)
    {
        if (entry->type != LIMINE_MEMMAP_USABLE)
        {
            continue;
        }

        const std::size_t start_page = entry->base / page_size;
        const std::size_t end_page = (entry->base + entry->length) / page_size;

        for (std::size_t page = start_page; page < end_page; ++page)
        {
            _bitmap.clear(page);
        }
    }
}

} // namespace nos
