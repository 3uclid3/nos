#pragma once

namespace nos {

template<class T>
struct remove_reference
{
    typedef T type;
};
template<class T>
struct remove_reference<T&>
{
    typedef T type;
};
template<class T>
struct remove_reference<T&&>
{
    typedef T type;
};

template<typename T>
using remove_reference_t = remove_reference<T>::type;

} // namespace nos
