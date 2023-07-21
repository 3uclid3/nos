#pragma once

#include <base-types.hpp>

namespace nos {

template<typename T>
class Array
{
public:
    constexpr Array() = default;

private:
    T* _first{nullptr};
    size_t _size{0};
    size_t _capacity{0};
};

template<typename T, size_t TSize>
class InplaceArray : public Array<T>
{
public:
    constexpr InplaceArray();

private:
    T _inplace[TSize];
};

} // namespace nos
