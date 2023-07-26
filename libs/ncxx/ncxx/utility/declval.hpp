#pragma once

namespace NOS {

namespace Details {
template<typename T>
T&& declvalImpl(int);

template<typename T>
T declvalImpl(long);

} // namespace Details

template<typename T>
decltype(NOS::Details::declvalImpl<T>(0)) declval();

} // namespace NOS
