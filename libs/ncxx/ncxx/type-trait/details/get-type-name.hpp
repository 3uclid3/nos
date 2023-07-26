#pragma once

#include <ncxx/string/string-view.hpp>
#include <ncxx/type-trait/details/get-type-full-name.hpp>

namespace NOS::Details {

template<typename T>
constexpr StringView getTypeName()
{
    const StringView name = getTypeFullName<T>();

    const size_t delimiter = name.findLastOf(':');

    return delimiter != StringView::NPOS ? name.substr(delimiter + 1) : name;
}

} // namespace NOS::Details
