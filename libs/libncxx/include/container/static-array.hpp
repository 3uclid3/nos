#pragma once

#include <base-types.hpp>
#include <debug/assert.hpp>
#include <type-traits/is-const.hpp>

namespace N {

template<typename T, size_t Size>
class StaticArray
{
public:
    using ValueType = T;

    using reference = ValueType&;
    using const_reference = const ValueType&;

    using Iterator = ValueType*;
    using ConstIterator = const ValueType*;

    using pointer = ValueType*;
    using const_pointer = const ValueType*;

    using size_type = size_t;
    using difference_type = ptrdiff_t;

public:
    void fill(const ValueType& value);
    void swap(StaticArray& other);

public:
    constexpr ConstIterator begin() const;
    constexpr ConstIterator end() const;

    constexpr ConstIterator cbegin() const;
    constexpr ConstIterator cend() const;

    constexpr Iterator begin();
    constexpr Iterator end();

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

    constexpr const ValueType* data() const;
    constexpr ValueType* data();

public:
    T _data[Size];
};

template<typename T>
class StaticArray<T, 0>
{
public:
    using ValueType = T;

    using reference = ValueType&;
    using const_reference = const ValueType&;

    using Iterator = ValueType*;
    using ConstIterator = const ValueType*;

    using pointer = ValueType*;
    using const_pointer = const ValueType*;

    using size_type = size_t;
    using difference_type = ptrdiff_t;

public:
    void fill(const ValueType& value);
    void swap(StaticArray& other);

public:
    constexpr ConstIterator begin() const;
    constexpr ConstIterator end() const;

    constexpr ConstIterator cbegin() const;
    constexpr ConstIterator cend() const;

    constexpr Iterator begin();
    constexpr Iterator end();

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

    constexpr const ValueType* data() const;
    constexpr ValueType* data();
};

template<typename T, size_t Size>
void StaticArray<T, Size>::fill(const ValueType& value)
{
    for (T& v : *this)
    {
        v = value;
    }
}

template<typename T, size_t Size>
void StaticArray<T, Size>::swap(StaticArray& other)
{
    // static_assert(false, "To be implemented");
    N_UNUSED(other);
}

template<typename T, size_t Size>
constexpr StaticArray<T, Size>::Iterator StaticArray<T, Size>::begin()
{
    return Iterator(data());
}

template<typename T, size_t Size>
constexpr StaticArray<T, Size>::ConstIterator StaticArray<T, Size>::begin() const
{
    return ConstIterator(data());
}

template<typename T, size_t Size>
constexpr StaticArray<T, Size>::Iterator StaticArray<T, Size>::end()
{
    return Iterator(data() + Size);
}
template<typename T, size_t Size>
constexpr StaticArray<T, Size>::ConstIterator StaticArray<T, Size>::end() const
{
    return ConstIterator(data() + Size);
}
template<typename T, size_t Size>
constexpr StaticArray<T, Size>::ConstIterator StaticArray<T, Size>::cbegin() const
{
    return begin();
}
template<typename T, size_t Size>
constexpr StaticArray<T, Size>::ConstIterator StaticArray<T, Size>::cend() const
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
    N_ASSERT(index < Size, "out-of-bounds access in StaticArray<T, N>");
    return _data[index];
}

template<typename T, size_t Size>
constexpr StaticArray<T, Size>::const_reference StaticArray<T, Size>::operator[](size_type index) const
{
    N_ASSERT(index < Size, "out-of-bounds access in StaticArray<T, N>");
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
constexpr const StaticArray<T, Size>::ValueType* StaticArray<T, Size>::data() const
{
    return _data;
}

template<typename T, size_t Size>
constexpr StaticArray<T, Size>::ValueType* StaticArray<T, Size>::data()
{
    return _data;
}

template<typename T>
void StaticArray<T, 0>::fill(const ValueType& value)
{
    static_assert(!IsConstV<T>, "cannot fill zero-sized StaticArray of type 'const T'");
    N_UNUSED(value);
}

template<typename T>
void StaticArray<T, 0>::swap(StaticArray& other)
{
    static_assert(!IsConstV<T>, "cannot swap zero-sized StaticArray of type 'const T'");
    N_UNUSED(other);
}

template<typename T>
constexpr StaticArray<T, 0>::Iterator StaticArray<T, 0>::begin()
{
    return Iterator(data());
}

template<typename T>
constexpr StaticArray<T, 0>::ConstIterator StaticArray<T, 0>::begin() const
{
    return ConstIterator(data());
}

template<typename T>
constexpr StaticArray<T, 0>::Iterator StaticArray<T, 0>::end()
{
    return Iterator(data());
}

template<typename T>
constexpr StaticArray<T, 0>::ConstIterator StaticArray<T, 0>::end() const
{
    return ConstIterator(data());
}

template<typename T>
constexpr StaticArray<T, 0>::ConstIterator StaticArray<T, 0>::cbegin() const
{
    return begin();
}

template<typename T>
constexpr StaticArray<T, 0>::ConstIterator StaticArray<T, 0>::cend() const
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
    N_ASSERT(false, "cannot call StaticArray<T, 0>:::operator[] on a zero-sized StaticArray");
    N_UNUSED(index);
    N_UNREACHABLE();
}

template<typename T>
constexpr StaticArray<T, 0>::const_reference StaticArray<T, 0>::operator[](size_type index) const
{
    N_ASSERT(false, "cannot call StaticArray<T, 0>:::operator[] on a zero-sized StaticArray");
    N_UNUSED(index);
    N_UNREACHABLE();
}

template<typename T>
constexpr StaticArray<T, 0>::const_reference StaticArray<T, 0>::first() const
{
    N_ASSERT(false, "cannot call StaticArray<T, 0>::first() on a zero-sized StaticArray");
    N_UNREACHABLE();
}

template<typename T>
constexpr StaticArray<T, 0>::reference StaticArray<T, 0>::first()
{
    N_ASSERT(false, "cannot call StaticArray<T, 0>::first() on a zero-sized StaticArray");
    N_UNREACHABLE();
}

template<typename T>
constexpr StaticArray<T, 0>::const_reference StaticArray<T, 0>::last() const
{
    N_ASSERT(false, "cannot call StaticArray<T, 0>::data() on a zero-sized StaticArray");
    N_UNREACHABLE();
}

template<typename T>
constexpr StaticArray<T, 0>::reference StaticArray<T, 0>::last()
{
    N_ASSERT(false, "cannot call StaticArray<T, 0>::data() on a zero-sized StaticArray");
    N_UNREACHABLE();
}

template<typename T>
constexpr const StaticArray<T, 0>::ValueType* StaticArray<T, 0>::data() const
{
    return nullptr;
}

template<typename T>
constexpr StaticArray<T, 0>::ValueType* StaticArray<T, 0>::data()
{
    return nullptr;
}

} // namespace N
