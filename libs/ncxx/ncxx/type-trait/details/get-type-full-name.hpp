#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/string/string-view.hpp>

namespace NOS::Details {

template<typename T>
constexpr StringView getTypeFullName()
{
    constexpr size_t size = sizeof(__PRETTY_FUNCTION__);
    constexpr size_t prefixSize = sizeof("StringView NOS::Details::getTypeFullName() [T = ");
    constexpr size_t suffixSize = sizeof("]");
    constexpr size_t typeSize = size - prefixSize - suffixSize + 1;

    return StringView(__PRETTY_FUNCTION__ + prefixSize - 1, typeSize);
}

} // namespace NOS::Details
