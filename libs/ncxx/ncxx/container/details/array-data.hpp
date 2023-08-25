#pragma once

#include <ncxx/algorithm/clamp.hpp>
#include <ncxx/basic-types.hpp>
#include <ncxx/debug/assert.hpp>

namespace NOS::Details {

template<typename TSize>
class ArrayData
{
public:
    using DataSizeType = TSize;

    constexpr bool isEmpty() const;
    constexpr size_t size() const;
    constexpr size_t capacity() const;

protected:
    constexpr size_t getNextCapacity(size_t minSize) const;

protected:
    constexpr ArrayData() = default;
    constexpr ArrayData(void* pointer, size_t capacity);

    void* _buffer{nullptr};
    DataSizeType _size{0};
    DataSizeType _capacity{0};
};

template<typename TSize>
constexpr bool ArrayData<TSize>::isEmpty() const
{
    return size() == 0;
}

template<typename TSize>
constexpr size_t ArrayData<TSize>::size() const
{
    return _size;
}

template<typename TSize>
constexpr size_t ArrayData<TSize>::capacity() const
{
    return _capacity;
}

template<typename TSize>
constexpr ArrayData<TSize>::ArrayData(void* buffer, size_t capacity)
    : _buffer(buffer)
    , _capacity(static_cast<DataSizeType>(capacity))
{
}

template<typename TSize>
constexpr size_t ArrayData<TSize>::getNextCapacity(size_t minSize) const
{
    constexpr size_t maxSize = static_cast<TSize>(-1);

    NOS_ASSERT(minSize <= maxSize);
    NOS_ASSERT(_capacity < maxSize);

    const size_t newCapacity = _capacity * 2 + 1;
    return clamp(newCapacity, minSize, maxSize);
}

} // namespace NOS::Details
