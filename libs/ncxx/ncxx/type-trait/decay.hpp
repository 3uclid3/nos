#pragma once

namespace NOS {

template<typename T>
struct Decay
{
    using Type = __decay(T);
};

template<typename T>
using DecayT = Decay<T>::Type;

} // namespace NOS
