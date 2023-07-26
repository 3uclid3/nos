#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/string/string-view.hpp>
#include <ncxx/type-trait/is-enum-class.hpp>
#include <ncxx/type-trait/is-enum.hpp>

namespace NOS::Details {

template<typename T, T VALUE>
requires(IsEnumV<T>)
constexpr StringView getTypeEnumValueName()
{
    constexpr size_t prefixSize = sizeof("StringView NOS::Details::getTypeEnumValueName() [T = ");

    constexpr StringView func = __PRETTY_FUNCTION__;
    constexpr StringView funcNoPrefix = func.substr(prefixSize - 1);

    constexpr size_t index = funcNoPrefix.findLastOf(':');
    constexpr size_t startOffset = index != StringView::NPOS ? 1 : 2;
    constexpr size_t endOffset = index != StringView::NPOS ? 2 : 3;
    constexpr size_t adjustedIndex = index != StringView::NPOS ? index : funcNoPrefix.findLastOf('=');

    return funcNoPrefix.substr(adjustedIndex + startOffset, funcNoPrefix.size() - adjustedIndex - endOffset);
}

} // namespace NOS::Details