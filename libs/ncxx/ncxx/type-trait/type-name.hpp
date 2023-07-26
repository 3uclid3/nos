#pragma once

#include <ncxx/string/string-view.hpp>
#include <ncxx/type-trait/details/get-type-name.hpp>

namespace NOS {

template<typename T>
struct TypeName
{
    static constexpr StringView Value{Details::getTypeName<T>()};
};

template<typename T>
constexpr StringView TypeNameV{TypeName<T>::Value};

} // namespace NOS
