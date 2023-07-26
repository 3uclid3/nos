#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/container/static-array.hpp>
#include <ncxx/debug/assert.hpp>
#include <ncxx/memory/pointer-traits.hpp>
#include <ncxx/type-trait/remove-const-volatile.hpp>

namespace NOS {

namespace Details {

// template<class TFrom, class TTo>
// concept SpanArrayConvertible = IsConvertibleV<TFrom (*)[], TTo (*)[]>;

// template<class TIt, class T>
// concept SpanCompatibleIterator = ContiguousIterator<TIt> && SpanArrayConvertible<RemoveReferenceT<iter_reference_t<TIt>>, T>;

} // namespace Details

inline constexpr size_t DynamicExtent = static_cast<size_t>(-1);

template<typename T, size_t TExtent = DynamicExtent>
class Span;

template<typename T, size_t TExtent>
class Span
{
public:
    using ElementType = T;
    using ValueType = RemoveConstVolatileT<T>;

    using SizeType = size_t;
    using DifferenceType = ptrdiff_t;

    using Pointer = T*;
    using ConstPointer = const T*;

    using Reference = T&;
    using ConstReference = const T&;

    using Iterator = Pointer;
    using ConstIterator = ConstPointer;

    static constexpr SizeType Extent = TExtent;

public:
    template<size_t TSize = TExtent>
    requires(TSize == 0)
    constexpr Span();

    constexpr Span(const Span&) = default;
    constexpr Span& operator=(const Span&) = default;

    constexpr ConstReference operator[](SizeType index) const;
    constexpr Reference operator[](SizeType index);

    constexpr ConstIterator begin() const;
    constexpr ConstIterator end() const;

    constexpr ConstIterator cbegin() const;
    constexpr ConstIterator cend() const;

    constexpr Iterator begin();
    constexpr Iterator end();

    constexpr ConstPointer data() const;
    constexpr Pointer data();

private:
    Pointer _data{nullptr};
};

template<typename T>
class Span<T, DynamicExtent>
{
public:
    using ElementType = T;
    using ValueType = RemoveConstVolatileT<T>;

    using SizeType = size_t;
    using DifferenceType = ptrdiff_t;

    using Pointer = T*;
    using ConstPointer = const T*;

    using Reference = T&;
    using ConstReference = const T&;

    using Iterator = Pointer;
    using ConstIterator = ConstPointer;

    static constexpr SizeType Extent = DynamicExtent;

public:
    constexpr Span() = default;

    constexpr Span(const Span&) = default;
    constexpr Span& operator=(const Span&) = default;

    template<size_t TSize>
    constexpr Span(ElementType (&array)[TSize]);

    template<typename OtherElementType, size_t TSize>
    constexpr Span(StaticArray<OtherElementType, TSize>& staticArray);

    template<typename OtherElementType, size_t TSize>
    constexpr Span(const StaticArray<OtherElementType, TSize>& staticArray);

    template<typename TIt>
    constexpr Span(TIt first, SizeType size);

    template<typename TIt, typename TEnd>
    constexpr Span(TIt first, TEnd last);

    constexpr ConstReference operator[](SizeType index) const;
    constexpr Reference operator[](SizeType index);

    constexpr ConstIterator begin() const;
    constexpr ConstIterator end() const;

    constexpr ConstIterator cbegin() const;
    constexpr ConstIterator cend() const;

    constexpr Iterator begin();
    constexpr Iterator end();

    constexpr ConstPointer data() const;
    constexpr Pointer data();

private:
    Pointer _data{nullptr};
    SizeType _size{0};
};

template<typename T, size_t TExtent>
template<size_t TSize>
requires(TSize == 0)
constexpr Span<T, TExtent>::Span()
{}

template<typename T, size_t TExtent>
constexpr Span<T, TExtent>::ConstReference Span<T, TExtent>::operator[](SizeType index) const
{
    NOS_ASSERT(index < TExtent);
    return _data[index];
}

template<typename T, size_t TExtent>
constexpr Span<T, TExtent>::Reference Span<T, TExtent>::operator[](SizeType index)
{
    NOS_ASSERT(index < TExtent);
    return _data[index];
}

template<typename T, size_t TExtent>
constexpr Span<T, TExtent>::ConstIterator Span<T, TExtent>::begin() const
{
    return _data;
}

template<typename T, size_t TExtent>
constexpr Span<T, TExtent>::ConstIterator Span<T, TExtent>::end() const
{
    return _data + TExtent;
}

template<typename T, size_t TExtent>
constexpr Span<T, TExtent>::ConstIterator Span<T, TExtent>::cbegin() const
{
    return begin();
}

template<typename T, size_t TExtent>
constexpr Span<T, TExtent>::ConstIterator Span<T, TExtent>::cend() const
{
    return end();
}

template<typename T, size_t TExtent>
constexpr Span<T, TExtent>::ConstPointer Span<T, TExtent>::data() const
{
    return _data;
}

template<typename T, size_t TExtent>
constexpr Span<T, TExtent>::Pointer Span<T, TExtent>::data()
{
    return _data;
}

template<typename T, size_t TExtent>
constexpr Span<T, TExtent>::Iterator Span<T, TExtent>::begin()
{
    return _data;
}

template<typename T, size_t TExtent>
constexpr Span<T, TExtent>::Iterator Span<T, TExtent>::end()
{
    return _data + TExtent;
}

template<typename T>
template<size_t TSize>
constexpr Span<T, DynamicExtent>::Span(ElementType (&array)[TSize])
    : _data(toAddress(array))
    , _size(TSize)
{}

template<typename T>
template<typename OtherElementType, size_t TSize>
constexpr Span<T, DynamicExtent>::Span(StaticArray<OtherElementType, TSize>& staticArray)
    : _data(staticArray.data())
    , _size(TSize)
{
}

template<typename T>
template<typename OtherElementType, size_t TSize>
constexpr Span<T, DynamicExtent>::Span(const StaticArray<OtherElementType, TSize>& staticArray)
    : _data(staticArray.data())
    , _size(TSize)
{
}

template<typename T>
template<typename TIt>
constexpr Span<T, DynamicExtent>::Span(TIt first, SizeType size)
    : _data(toAddress(first))
    , _size(size)
{}

template<typename T>
template<typename TIt, typename TEnd>
constexpr Span<T, DynamicExtent>::Span(TIt first, TEnd last)
    : _data(toAddress(first))
    , _size(last - first)
{}

template<typename T>
constexpr Span<T, DynamicExtent>::ConstReference Span<T, DynamicExtent>::operator[](SizeType index) const
{
    NOS_ASSERT(index < _size);
    return _data[index];
}

template<typename T>
constexpr Span<T, DynamicExtent>::Reference Span<T, DynamicExtent>::operator[](SizeType index)
{
    NOS_ASSERT(index < _size);
    return _data[index];
}

template<typename T>
constexpr Span<T, DynamicExtent>::ConstIterator Span<T, DynamicExtent>::begin() const
{
    return _data;
}

template<typename T>
constexpr Span<T, DynamicExtent>::ConstIterator Span<T, DynamicExtent>::end() const
{
    return _data + _size;
}

template<typename T>
constexpr Span<T, DynamicExtent>::ConstIterator Span<T, DynamicExtent>::cbegin() const
{
    return begin();
}

template<typename T>
constexpr Span<T, DynamicExtent>::ConstIterator Span<T, DynamicExtent>::cend() const
{
    return end();
}

template<typename T>
constexpr Span<T, DynamicExtent>::Iterator Span<T, DynamicExtent>::begin()
{
    return _data;
}

template<typename T>
constexpr Span<T, DynamicExtent>::Iterator Span<T, DynamicExtent>::end()
{
    return _data + _size;
}

template<typename T>
constexpr Span<T, DynamicExtent>::ConstPointer Span<T, DynamicExtent>::data() const
{
    return _data;
}

template<typename T>
constexpr Span<T, DynamicExtent>::Pointer Span<T, DynamicExtent>::data()
{
    return _data;
}

} // namespace NOS
