#pragma once

#include <base_types.hpp>

namespace nos {

template<typename T, size_t Size>
class static_array
{
public:
    using value_type = T;

    using reference = value_type&;
    using const_reference = const value_type&;

    using iterator = value_type*;
    using const_iterator = const value_type*;

    using pointer = value_type*;
    using const_pointer = const value_type*;

    using size_type = size_t;
    using difference_type = ptrdiff_t;

public:
    void fill(const value_type& value);
    void swap(static_array& other);

public:
    constexpr const_iterator begin() const;
    constexpr const_iterator end() const;

    constexpr const_iterator cbegin() const;
    constexpr const_iterator cend() const;

    constexpr iterator begin();
    constexpr iterator end();

public:
    constexpr size_type size() const;

    constexpr size_type max_size() const;
    constexpr bool is_empty() const;

public:
    constexpr const_reference operator[](size_type index) const;
    constexpr reference operator[](size_type index);

    constexpr const_reference at(size_type index) const;
    constexpr reference at(size_type index);

    constexpr const_reference first() const;
    constexpr reference first();

    constexpr const_reference last() const;
    constexpr reference last();

    constexpr const value_type* data() const;
    constexpr value_type* data();

public:
    T _data[Size];
};

template<typename T, size_t Size>
void static_array<T, Size>::fill(const value_type& value)
{
}

template<typename T, size_t Size>
void static_array<T, Size>::swap(static_array& other)
{
}

template<typename T, size_t Size>
constexpr static_array<T, Size>::iterator static_array<T, Size>::begin()
{
    return iterator(data());
}

template<typename T, size_t Size>
constexpr static_array<T, Size>::const_iterator static_array<T, Size>::begin() const
{
    return const_iterator(data());
}

template<typename T, size_t Size>
constexpr static_array<T, Size>::iterator static_array<T, Size>::end()
{
    return iterator(data() + Size);
}
template<typename T, size_t Size>
constexpr static_array<T, Size>::const_iterator static_array<T, Size>::end() const
{
    return const_iterator(data() + Size);
}
template<typename T, size_t Size>
constexpr static_array<T, Size>::const_iterator static_array<T, Size>::cbegin() const
{
    return begin();
}
template<typename T, size_t Size>
constexpr static_array<T, Size>::const_iterator static_array<T, Size>::cend() const
{
    return end();
}

template<typename T, size_t Size>
constexpr static_array<T, Size>::size_type static_array<T, Size>::size() const
{
    return Size;
}

template<typename T, size_t Size>
constexpr static_array<T, Size>::size_type static_array<T, Size>::max_size() const
{
    return Size;
}

template<typename T, size_t Size>
constexpr bool static_array<T, Size>::is_empty() const
{
    return false;
}

// element access:

template<typename T, size_t Size>
reference operator[](size_type __n)
{
    NOS_ASSERT(__n < _Size, "out-of-bounds access in std::array<T, N>");
    return __elems_[__n];
}
template<typename T, size_t Size>
const_reference operator[](size_type __n) const
{
    NOS_ASSERT(__n < _Size, "out-of-bounds access in std::array<T, N>");
    return __elems_[__n];
}

template<typename T, size_t Size>
reference at(size_type __n)
{
    if (__n >= _Size)
        __throw_out_of_range("array::at");
    return __elems_[__n];
}

template<typename T, size_t Size>
const_reference at(size_type __n) const
{
    if (__n >= _Size)
        __throw_out_of_range("array::at");
    return __elems_[__n];
}

reference front() { return (*this)[0]; }
const_reference front() const { return (*this)[0]; }
reference back() { return (*this)[_Size - 1]; }
constexpr const_reference back() const { return (*this)[_Size - 1]; }

value_type* data() { return _data; }

const value_type* data() const { return _data; }

} // namespace nos
