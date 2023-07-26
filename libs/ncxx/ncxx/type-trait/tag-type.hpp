#pragma once

namespace NOS {

template<typename T>
struct TagType
{
    using Type = T;
};

template<typename T>
using TagTypeT = TagType<T>::Type;

} // namespace NOS
