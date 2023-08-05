#pragma once

#include <ncxx/type-trait/is-array.hpp>

#if __has_feature(address_sanitizer)
extern "C" int __sanitizer_verify_contiguous_container(const void* beg, const void* mid, const void* end);

namespace NOS::ASan {

template<typename T>
constexpr bool verifyContiguousContainer(const T& c)
{
    if (c.data() == nullptr)
    {
        return true;
    }
    return __sanitizer_verify_contiguous_container(
               c.data(),
               c.data() + c.size(),
               c.data() + c.capacity())
           != 0;
}

} // namespace NOS::ASan
#else

#error fuck
namespace NOS::Test {

template<typename T>
requires(IsArrayV<T>)
constexpr bool isContiguousContainerASanCorrect(const T&)
{
    return true;
}

} // namespace NOS::Test
#endif // __has_feature(address_sanitizer)
