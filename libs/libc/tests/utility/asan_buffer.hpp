#pragma once

#include <cassert>
#include <cstddef>
#include <cstdlib>

#if __has_feature(address_sanitizer) || defined(__SANITIZE_ADDRESS__)
#define ASAN_POISON_MEMORY_REGION(addr, size) \
    __asan_poison_memory_region((addr), (size))
#define ASAN_UNPOISON_MEMORY_REGION(addr, size) \
    __asan_unpoison_memory_region((addr), (size))
#else
#define ASAN_POISON_MEMORY_REGION(addr, size) \
    ((void)(addr), (void)(size))
#define ASAN_UNPOISON_MEMORY_REGION(addr, size) \
    ((void)(addr), (void)(size))
#endif

class asan_poisoned_buffer
{
public:
    static constexpr std::size_t align = 64;
    static constexpr std::size_t leeway = align * 2;

public:
    asan_poisoned_buffer(std::size_t size)
        : _ptr(std::malloc(size))
    {
        ASAN_POISON_MEMORY_REGION(_ptr, size);
    }

    ~asan_poisoned_buffer()
    {
        std::free(_ptr);
    }

protected:
    void* _ptr;
};

class asan_buffer : private asan_poisoned_buffer
{
public:
    enum class aligned : bool
    {
        no = false,
        yes = true
    };

    static constexpr std::size_t align = 64;
    static constexpr std::size_t threshold = align * 2;

public:
    asan_buffer(std::size_t size, aligned aligned = aligned::yes)
        : asan_poisoned_buffer(size + threshold)
        , _size(size)
    {
        _offset_ptr = reinterpret_cast<char*>(_ptr);
        _offset_ptr += distance_to_next_aligned<align>(_ptr);

        if (aligned == aligned::no)
        {
            ++_offset_ptr;
        }

        ASAN_UNPOISON_MEMORY_REGION(_offset_ptr, _size);
    }

    asan_buffer(const asan_buffer& other)
        : asan_poisoned_buffer(other._size + threshold)
        , _size(other._size)
    {
        _offset_ptr = reinterpret_cast<char*>(_ptr);
        _offset_ptr += other._offset_ptr - reinterpret_cast<char*>(other._ptr);

        ASAN_UNPOISON_MEMORY_REGION(_offset_ptr, _size);

        for (size_t i = 0; i < _size; ++i)
        {
            _offset_ptr[i] = other._offset_ptr[i];
        }
    }

    asan_buffer& operator=(const asan_buffer& other)
    {
        assert(_size <= other._size);

        for (size_t i = 0; i < _size; ++i)
        {
            _offset_ptr[i] = other._offset_ptr[i];
        }

        return *this;
    }

    char operator[](std::size_t index) const { return _offset_ptr[index]; }
    char& operator[](std::size_t index) { return _offset_ptr[index]; }

    std::size_t size() const { return _size; }

    const char* begin() const { return reinterpret_cast<char*>(_offset_ptr); }
    const char* end() const { return reinterpret_cast<char*>(_offset_ptr + _size); }

    char* begin() { return reinterpret_cast<char*>(_offset_ptr); }
    char* end() { return reinterpret_cast<char*>(_offset_ptr + _size); }

    void initialize(char start = 1)
    {
        char c = start;
        for (char& ch : *this)
        {
            ch = c++;
        }
    }

private:
    static constexpr bool is_power2(std::size_t value)
    {
        return value != 0 && !(value & (value -1));
    }

    template<std::size_t Alignment>
    static std::uintptr_t distance_to_align_down(const void* ptr)
    {
        static_assert(is_power2(Alignment), "alignment must be a power of 2");
        return reinterpret_cast<uintptr_t>(ptr) & (Alignment - 1U);
    }

    template<std::size_t Alignment>
    static std::uintptr_t distance_to_next_aligned(const void* ptr)
    {
        return Alignment - distance_to_align_down<Alignment>(ptr);
    }

    std::size_t _size{0};
    char* _offset_ptr{nullptr};
};
