#pragma once

#include <base-types.hpp>
#include <memory/pointer-traits.hpp>
#include <type-traits/remove-const-volatile.hpp>

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

    constexpr ConstIterator begin() const;
    constexpr ConstIterator end() const;

    constexpr Iterator begin();
    constexpr Iterator end();

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

    template<typename TIt>
    constexpr Span(TIt first, SizeType size);

    template<typename TIt, typename TEnd>
    constexpr Span(TIt first, TEnd last);

    constexpr ConstIterator begin() const;
    constexpr ConstIterator end() const;

    constexpr Iterator begin();
    constexpr Iterator end();

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
constexpr Span<T, DynamicExtent>::Span(ElementType(&array)[TSize])
    : _data{toAddress(array)}
    , _size{TSize}
{}

template<typename T>
template<typename TIt>
constexpr Span<T, DynamicExtent>::Span(TIt first, SizeType size)
    : _data{toAddress(first)}
    , _size{size}
{}

template<typename T>
template<typename TIt, typename TEnd>
constexpr Span<T, DynamicExtent>::Span(TIt first, TEnd last)
    : _data(toAddress(first))
    , _size(last - first)
{}

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
constexpr Span<T, DynamicExtent>::Iterator Span<T, DynamicExtent>::begin()
{
    return _data;
}

template<typename T>
constexpr Span<T, DynamicExtent>::Iterator Span<T, DynamicExtent>::end()
{
    return _data + _size;
}

} // namespace NOS
