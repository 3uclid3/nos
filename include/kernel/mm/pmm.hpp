#pragma once

#include <cstdint>
#include <span>

struct limine_memmap_entry;

namespace nos {

class pmm
{
public:
    void init();

    std::uintptr_t tohh(std::uintptr_t phaddr) const;
    std::uintptr_t toph(std::uintptr_t hhaddr) const;

    [[nodiscard]] void* allocate_pages(std::size_t count = 1);
    void deallocate_pages(void* ptr, std::size_t count = 1);

    template<typename T>
    T* allocate_pages(std::size_t count = 1);

    std::size_t total_size() const;
    std::size_t used_size() const;
    std::size_t usable_size() const;

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

        std::size_t size() const;

    private:
        std::span<std::uint8_t> _data;
    };

    bitmap _bitmap;

    std::uintptr_t _hhdm_offset{0};

    std::size_t _total_size{0};
    std::size_t _used_size{0};
    std::size_t _usable_size{0};

    std::uintptr_t _max_base_address{0};
    std::uintptr_t _max_usable_base_address{0};
};

inline std::size_t pmm::bitmap::size() const
{
    return _data.size() * 8;
}

inline std::uintptr_t pmm::tohh(std::uintptr_t phaddr) const
{
    return phaddr + _hhdm_offset;
}

inline std::uintptr_t pmm::toph(std::uintptr_t hhaddr) const
{
    return hhaddr - _hhdm_offset;
}

template<typename T>
T* pmm::allocate_pages(std::size_t count)
{
    return reinterpret_cast<T*>(allocate_pages(count));
}

inline std::size_t pmm::total_size() const
{
    return _total_size;
}

inline std::size_t pmm::used_size() const
{
    return _used_size;
}

inline std::size_t pmm::usable_size() const
{
    return _usable_size;
}

} // namespace nos