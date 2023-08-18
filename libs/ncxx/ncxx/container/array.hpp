#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/config.hpp>
#include <ncxx/container/details/array-base-type.hpp>
#include <ncxx/container/details/array-size-type.hpp>

namespace NOS {

using DefaultArrayAllocator = NOS_DEFAULT_ARRAY_ALLOCATOR;

template<typename T, typename TAllocator = DefaultArrayAllocator, typename TSize = Details::ArraySizeTypeT<T>>
class Array : public Details::ArrayBaseTypeT<T, TAllocator, TSize>
{
    using Base = typename Details::ArrayBaseTypeT<T, TAllocator, TSize>;

public:
    using typename Base::AllocatorType;

    using typename Base::ValueType;

    using typename Base::ConstPointer;
    using typename Base::Pointer;

    using typename Base::ConstReference;
    using typename Base::Reference;

    using typename Base::ConstIterator;
    using typename Base::Iterator;

public:
    constexpr Array() = default;
    constexpr Array(size_t initialSize);
    constexpr Array(size_t initialSize, const T& initialValue);
};

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::Array(size_t initialSize)
    : Base(initialSize)
{
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::Array(size_t initialSize, const T& initialValue)
    : Base(initialSize)
{
    for (T& v : *this)
    {
        v = initialValue;
    }
}

} // namespace NOS
