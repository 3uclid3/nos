#pragma once

#include <base-types.hpp>
#include <debug/assert.hpp>
#include <def.hpp>
#include <type-traits/is-const.hpp>
#include <type-traits/remove-const-volatile.hpp>
#include <utility/integer-sequence.hpp>
#include <utility/move.hpp>

namespace NOS {

template<typename T, size_t TSize>
class StaticArray;

template<typename T, size_t TSize>
constexpr StaticArray<RemoveConstVolatileT<T>, TSize> toStaticArray(T (&array)[TSize]);

template<typename T, size_t TSize>
constexpr StaticArray<RemoveConstVolatileT<T>, TSize> toStaticArray(T (&&array)[TSize]);

template<typename T, size_t TSize>
class StaticArray
{
public:
    using ValueType = T;

    using Reference = ValueType&;
    using ConstReference = const ValueType&;

    using Iterator = ValueType*;
    using ConstIterator = const ValueType*;

    using Pointer = ValueType*;
    using ConstPointer = const ValueType*;

    using SizeType = size_t;
    using DifferenceType = ptrdiff_t;

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
    constexpr SizeType size() const;

    constexpr SizeType maxSize() const;
    constexpr bool isEmpty() const;

public:
    constexpr ConstReference operator[](SizeType index) const;
    constexpr Reference operator[](SizeType index);

    constexpr ConstReference first() const;
    constexpr Reference first();

    constexpr ConstReference last() const;
    constexpr Reference last();

    constexpr const ValueType* data() const;
    constexpr ValueType* data();

public:
    T _data[TSize];
};

template<typename T>
class StaticArray<T, 0>
{
public:
    using ValueType = T;

    using Reference = ValueType&;
    using ConstReference = const ValueType&;

    using Iterator = ValueType*;
    using ConstIterator = const ValueType*;

    using pointer = ValueType*;
    using const_pointer = const ValueType*;

    using SizeType = size_t;
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
    constexpr SizeType size() const;

    constexpr SizeType maxSize() const;
    constexpr bool isEmpty() const;

public:
    constexpr ConstReference operator[](SizeType index) const;
    constexpr Reference operator[](SizeType index);

    constexpr ConstReference first() const;
    constexpr Reference first();

    constexpr ConstReference last() const;
    constexpr Reference last();

    constexpr const ValueType* data() const;
    constexpr ValueType* data();
};

namespace Details {

template<typename T, size_t TSize, size_t... TIndex>
constexpr StaticArray<RemoveConstVolatileT<T>, TSize> toStaticArrayLValue(T (&array)[TSize], IndexSequence<TIndex...>)
{
    return {{array[TIndex]...}};
}

template<typename T, size_t TSize, size_t... TIndex>
constexpr StaticArray<RemoveConstVolatileT<T>, TSize> toStaticArrayRValue(T (&&array)[TSize], IndexSequence<TIndex...>)
{
    return {{move(array[TIndex])...}};
}

} // namespace Details

template<typename T, size_t TSize>
constexpr StaticArray<RemoveConstVolatileT<T>, TSize> toStaticArray(T (&array)[TSize])
{
    return Details::toStaticArrayLValue(array, MakeIndexSequence<TSize>());
}

template<typename T, size_t TSize>
constexpr StaticArray<RemoveConstVolatileT<T>, TSize> toStaticArray(T (&&array)[TSize])
{
    return Details::toStaticArrayRValue(move(array), MakeIndexSequence<TSize>());
}

template<typename T, size_t TSize>
void StaticArray<T, TSize>::fill(const ValueType& value)
{
    for (T& v : *this)
    {
        v = value;
    }
}

template<typename T, size_t TSize>
void StaticArray<T, TSize>::swap(StaticArray& other)
{
    NOS_ASSERT(false, "To be implemented");
    NOS_UNUSED(other);
}

template<typename T, size_t TSize>
constexpr StaticArray<T, TSize>::Iterator StaticArray<T, TSize>::begin()
{
    return Iterator(data());
}

template<typename T, size_t TSize>
constexpr StaticArray<T, TSize>::ConstIterator StaticArray<T, TSize>::begin() const
{
    return ConstIterator(data());
}

template<typename T, size_t TSize>
constexpr StaticArray<T, TSize>::Iterator StaticArray<T, TSize>::end()
{
    return Iterator(data() + TSize);
}
template<typename T, size_t TSize>
constexpr StaticArray<T, TSize>::ConstIterator StaticArray<T, TSize>::end() const
{
    return ConstIterator(data() + TSize);
}
template<typename T, size_t TSize>
constexpr StaticArray<T, TSize>::ConstIterator StaticArray<T, TSize>::cbegin() const
{
    return begin();
}
template<typename T, size_t TSize>
constexpr StaticArray<T, TSize>::ConstIterator StaticArray<T, TSize>::cend() const
{
    return end();
}

template<typename T, size_t TSize>
constexpr StaticArray<T, TSize>::SizeType StaticArray<T, TSize>::size() const
{
    return TSize;
}

template<typename T, size_t TSize>
constexpr StaticArray<T, TSize>::SizeType StaticArray<T, TSize>::maxSize() const
{
    return TSize;
}

template<typename T, size_t TSize>
constexpr bool StaticArray<T, TSize>::isEmpty() const
{
    return false;
}

template<typename T, size_t TSize>
constexpr StaticArray<T, TSize>::Reference StaticArray<T, TSize>::operator[](SizeType index)
{
    NOS_ASSERT(index < TSize, "out-of-bounds access in StaticArray<T, N>");
    return _data[index];
}

template<typename T, size_t TSize>
constexpr StaticArray<T, TSize>::ConstReference StaticArray<T, TSize>::operator[](SizeType index) const
{
    NOS_ASSERT(index < TSize, "out-of-bounds access in StaticArray<T, N>");
    return _data[index];
}

template<typename T, size_t TSize>
constexpr StaticArray<T, TSize>::ConstReference StaticArray<T, TSize>::first() const
{
    return (*this)[0];
}

template<typename T, size_t TSize>
constexpr StaticArray<T, TSize>::Reference StaticArray<T, TSize>::first()
{
    return (*this)[0];
}

template<typename T, size_t TSize>
constexpr StaticArray<T, TSize>::ConstReference StaticArray<T, TSize>::last() const
{
    return (*this)[TSize - 1];
}

template<typename T, size_t TSize>
constexpr StaticArray<T, TSize>::Reference StaticArray<T, TSize>::last()
{
    return (*this)[TSize - 1];
}

template<typename T, size_t TSize>
constexpr const StaticArray<T, TSize>::ValueType* StaticArray<T, TSize>::data() const
{
    return _data;
}

template<typename T, size_t TSize>
constexpr StaticArray<T, TSize>::ValueType* StaticArray<T, TSize>::data()
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
constexpr StaticArray<T, 0>::SizeType StaticArray<T, 0>::size() const
{
    return 0;
}

template<typename T>
constexpr StaticArray<T, 0>::SizeType StaticArray<T, 0>::maxSize() const
{
    return 0;
}

template<typename T>
constexpr bool StaticArray<T, 0>::isEmpty() const
{
    return true;
}

template<typename T>
constexpr StaticArray<T, 0>::Reference StaticArray<T, 0>::operator[](SizeType index)
{
    NOS_ASSERT(false, "cannot call StaticArray<T, 0>:::operator[] on a zero-sized StaticArray");
    N_UNUSED(index);
    NOS_UNREACHABLE();
}

template<typename T>
constexpr StaticArray<T, 0>::ConstReference StaticArray<T, 0>::operator[](SizeType index) const
{
    NOS_ASSERT(false, "cannot call StaticArray<T, 0>:::operator[] on a zero-sized StaticArray");
    N_UNUSED(index);
    NOS_UNREACHABLE();
}

template<typename T>
constexpr StaticArray<T, 0>::ConstReference StaticArray<T, 0>::first() const
{
    NOS_ASSERT(false, "cannot call StaticArray<T, 0>::first() on a zero-sized StaticArray");
    NOS_UNREACHABLE();
}

template<typename T>
constexpr StaticArray<T, 0>::Reference StaticArray<T, 0>::first()
{
    NOS_ASSERT(false, "cannot call StaticArray<T, 0>::first() on a zero-sized StaticArray");
    NOS_UNREACHABLE();
}

template<typename T>
constexpr StaticArray<T, 0>::ConstReference StaticArray<T, 0>::last() const
{
    NOS_ASSERT(false, "cannot call StaticArray<T, 0>::data() on a zero-sized StaticArray");
    NOS_UNREACHABLE();
}

template<typename T>
constexpr StaticArray<T, 0>::Reference StaticArray<T, 0>::last()
{
    NOS_ASSERT(false, "cannot call StaticArray<T, 0>::data() on a zero-sized StaticArray");
    NOS_UNREACHABLE();
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

} // namespace NOS
