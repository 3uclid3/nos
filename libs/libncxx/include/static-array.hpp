#pragma once

#include <base-types.hpp>

namespace nos {

template<typename T, size_t Size>
class StaticArray
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
    void swap(StaticArray& other);

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

    constexpr const_reference first() const;
    constexpr reference first();

    constexpr const_reference last() const;
    constexpr reference last();

    constexpr const value_type* data() const;
    constexpr value_type* data();

public:
    T _data[Size];
};

template<typename T>
class StaticArray<T, 0>
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
    void swap(StaticArray& other);

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
void StaticArray<T, Size>::fill(const value_type& value)
{
    for (T& v : *this)
    {
        v = value;
    }
}

template<typename T, size_t Size>
void StaticArray<T, Size>::swap(StaticArray& other)
{
    static_assert(false, "To be implemented");
    NOS_UNUSED(other);
}

template<typename T, size_t Size>
constexpr StaticArray<T, Size>::iterator StaticArray<T, Size>::begin()
{
    return iterator(data());
}

template<typename T, size_t Size>
constexpr StaticArray<T, Size>::const_iterator StaticArray<T, Size>::begin() const
{
    return const_iterator(data());
}

template<typename T, size_t Size>
constexpr StaticArray<T, Size>::iterator StaticArray<T, Size>::end()
{
    return iterator(data() + Size);
}
template<typename T, size_t Size>
constexpr StaticArray<T, Size>::const_iterator StaticArray<T, Size>::end() const
{
    return const_iterator(data() + Size);
}
template<typename T, size_t Size>
constexpr StaticArray<T, Size>::const_iterator StaticArray<T, Size>::cbegin() const
{
    return begin();
}
template<typename T, size_t Size>
constexpr StaticArray<T, Size>::const_iterator StaticArray<T, Size>::cend() const
{
    return end();
}

template<typename T, size_t Size>
constexpr StaticArray<T, Size>::size_type StaticArray<T, Size>::size() const
{
    return Size;
}

template<typename T, size_t Size>
constexpr StaticArray<T, Size>::size_type StaticArray<T, Size>::max_size() const
{
    return Size;
}

template<typename T, size_t Size>
constexpr bool StaticArray<T, Size>::is_empty() const
{
    return false;
}

template<typename T, size_t Size>
constexpr StaticArray<T, Size>::reference StaticArray<T, Size>::operator[](size_type index)
{
    NOS_ASSERT(index < Size, "out-of-bounds access in StaticArray<T, N>");
    return _data[index];
}

template<typename T, size_t Size>
constexpr StaticArray<T, Size>::const_reference StaticArray<T, Size>::operator[](size_type index) const
{
    NOS_ASSERT(index < Size, "out-of-bounds access in StaticArray<T, N>");
    return _data[index];
}

template<typename T, size_t Size>
constexpr StaticArray<T, Size>::const_reference StaticArray<T, Size>::first() const
{
    return (*this)[0];
}

template<typename T, size_t Size>
constexpr StaticArray<T, Size>::reference StaticArray<T, Size>::first()
{
    return (*this)[0];
}

template<typename T, size_t Size>
constexpr StaticArray<T, Size>::const_reference StaticArray<T, Size>::last() const
{
    return (*this)[Size - 1];
}

template<typename T, size_t Size>
constexpr StaticArray<T, Size>::reference StaticArray<T, Size>::last()
{
    return (*this)[Size - 1];
}

template<typename T, size_t Size>
constexpr const StaticArray<T, Size>::value_type* StaticArray<T, Size>::data() const
{
    return _data;
}

template<typename T, size_t Size>
constexpr StaticArray<T, Size>::value_type* StaticArray<T, Size>::data()
{
    return _data;
}

template<typename T>
void StaticArray<T, 0>::fill(const value_type& value)
{
    static_assert(!is_const<T>::value, "cannot fill zero-sized StaticArray of type 'const T'");
}

template<typename T>
void StaticArray<T, 0>::swap(StaticArray& other)
{
    static_assert(!is_const<T>::value, "cannot swap zero-sized StaticArray of type 'const T'");
}

template<typename T>
constexpr StaticArray<T, 0>::iterator StaticArray<T, 0>::begin()
{
    return iterator(data());
}

template<typename T>
constexpr StaticArray<T, 0>::const_iterator StaticArray<T, 0>::begin() const
{
    return const_iterator(data());
}

template<typename T>
constexpr StaticArray<T, 0>::iterator StaticArray<T, 0>::end()
{
    return iterator(data());
}

template<typename T>
constexpr StaticArray<T, 0>::const_iterator StaticArray<T, 0>::end() const
{
    return const_iterator(data());
}

template<typename T>
constexpr StaticArray<T, 0>::const_iterator StaticArray<T, 0>::cbegin() const
{
    return begin();
}

template<typename T>
constexpr StaticArray<T, 0>::const_iterator StaticArray<T, 0>::cend() const
{
    return end();
}

template<typename T>
constexpr StaticArray<T, 0>::size_type StaticArray<T, 0>::size() const
{
    return 0;
}

template<typename T>
constexpr StaticArray<T, 0>::size_type StaticArray<T, 0>::max_size() const
{
    return 0;
}

template<typename T>
constexpr bool StaticArray<T, 0>::is_empty() const
{
    return true;
}

template<typename T>
constexpr StaticArray<T, 0>::reference StaticArray<T, 0>::operator[](size_type index)
{
    NOS_ASSERT(false, "cannot call StaticArray<T, 0>:::operator[] on a zero-sized StaticArray");
    NOS_UNREACHABLE();
}

template<typename T>
constexpr StaticArray<T, 0>::const_reference StaticArray<T, 0>::operator[](size_type index) const
{
    NOS_ASSERT(false, "cannot call StaticArray<T, 0>:::operator[] on a zero-sized StaticArray");
    NOS_UNREACHABLE();
}

template<typename T>
constexpr StaticArray<T, 0>::const_reference StaticArray<T, 0>::first() const
{
    NOS_ASSERT(false, "cannot call StaticArray<T, 0>::first() on a zero-sized StaticArray");
    NOS_UNREACHABLE();
}

template<typename T>
constexpr StaticArray<T, 0>::reference StaticArray<T, 0>::first()
{
    NOS_ASSERT(false, "cannot call StaticArray<T, 0>::first() on a zero-sized StaticArray");
    NOS_UNREACHABLE();
}

template<typename T>
constexpr StaticArray<T, 0>::const_reference StaticArray<T, 0>::last() const
{
    NOS_ASSERT(false, "cannot call StaticArray<T, 0>::data() on a zero-sized StaticArray");
    NOS_UNREACHABLE();
}

template<typename T>
constexpr StaticArray<T, 0>::reference StaticArray<T, 0>::last()
{
    NOS_ASSERT(false, "cannot call StaticArray<T, 0>::data() on a zero-sized StaticArray");
    NOS_UNREACHABLE();
}

template<typename T>
constexpr const StaticArray<T, 0>::value_type* StaticArray<T, 0>::data() const
{
    return nullptr;
}

template<typename T>
constexpr StaticArray<T, 0>::value_type* StaticArray<T, 0>::data()
{
    return nullptr;
}

} // namespace nos
