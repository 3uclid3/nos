#pragma once

#include <ncxx/string/string-view.hpp>
#include <ncxx/type-trait/details/get-type-enum-value-name.hpp>

namespace NOS {

template<typename T, T TValue>
struct TypeEnumValueName
{
    static constexpr StringView Value{Details::getTypeEnumValueName<T, TValue>()};
};

template<typename T, T TValue>
constexpr StringView TypeEnumValueNameV{TypeEnumValueName<T, TValue>::Value};

} // namespace NOS
