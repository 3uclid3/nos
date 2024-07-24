#pragma once

#include <algorithm>
#include <cstdint>
#include <span>

#include <kdef.hpp>

struct limine_memmap_entry;

namespace nos {

constexpr std::size_t bytes_to_pages(std::size_t bytes);
constexpr std::size_t pages_to_bytes(std::size_t bytes);

class pmm
{
public:
    static constexpr std::size_t page_size = 0x1000;

    static inline std::uintptr_t tohh(std::uintptr_t physical_address)
    {
        return physical_address + _hhdm_offset;
    }

    static inline std::uintptr_t toph(std::uintptr_t high_half_address)
    {
        return high_half_address - _hhdm_offset;
    }

public:
    void init();

    HEDLEY_WARN_UNUSED_RESULT void* allocate_pages(std::size_t count = 1);
    void deallocate_pages(void* ptr, std::size_t count = 1);

    template<typename T>
    T* allocate_pages(std::size_t count = 1);

    std::size_t total_size() const { return _total_size; }
    std::size_t used_size() const { return _used_size; }
    std::size_t usable_size() const { return _usable_size; }

private:
    void init_bounds(std::span<limine_memmap_entry*> entries);
    void init_bitmap_buffer(std::span<limine_memmap_entry*> entries);
    void init_bitmap(std::span<limine_memmap_entry*> entries);

private:
    class bitmap
    {
    public:
        void init(std::span<std::uint8_t> data);

        void set(std::size_t index);
        void clear(std::size_t index);
        bool test(std::size_t index);

        std::size_t size() const { return _data.size() * 8; }

    private:
        std::span<std::uint8_t> _data;
    };

    bitmap _bitmap;

    std::size_t _total_size{0};
    std::size_t _used_size{0};
    std::size_t _usable_size{0};

    std::uintptr_t _max_base_address{0};
    std::uintptr_t _max_usable_base_address{0};

    inline static std::uintptr_t _hhdm_offset{0};
};

constexpr std::size_t bytes_to_pages(std::size_t bytes)
{
    return (bytes + pmm::page_size - 1) / pmm::page_size;
}

constexpr std::size_t pages_to_bytes(std::size_t bytes)
{
    return bytes * pmm::page_size;
}

template<typename T>
T* pmm::allocate_pages(std::size_t count)
{
    return reinterpret_cast<T*>(allocate_pages(count));
}

} // namespace nos