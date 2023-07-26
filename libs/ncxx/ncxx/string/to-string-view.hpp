#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/concept/integral.hpp>
#include <ncxx/container/span.hpp>
#include <ncxx/string/string-view.hpp>
#include <ncxx/type-trait/is-signed.hpp>

namespace NOS {

const StringView toStringView(Integral auto value, Span<char> buffer, int base = 10, bool upperCase = false)
{
    static constexpr StringView LowerCasesEntries{"zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"};
    static constexpr StringView UpperCasesEntries{"ZYXWVUTSRQPONMLKJIHGFEDCBA9876543210123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    if (base < 2 || base > 36)
    {
        return StringView{};
    }

    StringView entries = upperCase ? UpperCasesEntries : LowerCasesEntries;

    char* ptr = buffer.data();

    decltype(value) baseAsValueType = static_cast<decltype(value)>(base);
    decltype(value) tmpValue;

    do {
        tmpValue = value;
        value /= baseAsValueType;
        *ptr++ = entries[static_cast<StringView::SizeType>(35 + (tmpValue - value * baseAsValueType))];
    } while (value);

    if constexpr (IsSignedV<decltype(value)>)
    {
        if (tmpValue < 0)
            *ptr++ = '-';
    }

    const size_t size = static_cast<size_t>(ptr - buffer.data());

    *ptr-- = '\0';

    // Reverse the string
    char* front = buffer.data();
    while (front < ptr)
    {
        char tmpChar = *ptr;
        *ptr-- = *front;
        *front++ = tmpChar;
    }

    return {buffer.cbegin(), size};
}

} // namespace NOS
