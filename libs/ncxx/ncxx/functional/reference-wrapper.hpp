#pragma once

namespace NOS {

template<typename T>
class ReferenceWrapper
{
public:
    using Type = T;

    constexpr ReferenceWrapper(T& ptr)
        : _ptr(&ptr) {}

    constexpr operator Type&() const { return *_ptr; }
    constexpr Type& get() const { return *_ptr; }

private:
    T* _ptr;
};

template<class T>
void ref(const T&&) = delete;

template<class T>
void cref(const T&&) = delete;

template<typename T>
constexpr ReferenceWrapper<T> ref(T& v)
{
    return ReferenceWrapper<T>(v);
}

template<typename T>
constexpr ReferenceWrapper<T> ref(ReferenceWrapper<T> v)
{
    return v;
}

template<typename T>
constexpr ReferenceWrapper<const T> cref(const T& v)
{
    return ReferenceWrapper<const T>(v);
}

template<typename T>
constexpr ReferenceWrapper<const T> cref(ReferenceWrapper<T> v)
{
    return ReferenceWrapper<const T>(v.get());
}
} // namespace NOS
