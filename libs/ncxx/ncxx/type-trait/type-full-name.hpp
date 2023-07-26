#pragma once

#include <ncxx/string/string-view.hpp>
#include <ncxx/type-trait/details/get-type-full-name.hpp>

namespace NOS {

template<typename T>
struct TypeFullName
{
    static constexpr StringView Value{Details::getTypeFullName<T>()};
};

template<typename T>
constexpr StringView TypeFullNameV{TypeFullName<T>::Value};

} // namespace NOS
