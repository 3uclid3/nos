#pragma once

#include <string/to-string-view.hpp>

#include <base-types.hpp>
#include <container/span.hpp>
#include <container/static-array.hpp>
#include <string/format-argument.hpp>
#include <string/format-specification.hpp>
#include <string/string-view.hpp>

namespace NOS {

template<typename TOut, typename... TArguments>
void formatTo(TOut& out, StringView fmt, TArguments... rawArguments);

template<typename TOut>
void formatTo(TOut& out, StringView fmt, Span<FormatArgument> arguments);

template<typename TOut, typename... TArguments>
void formatTo(TOut& out, StringView fmt, TArguments... rawArguments)
{
    StaticArray arguments = makeFormatArguments(rawArguments...);
    formatTo(out, fmt, Span<FormatArgument>(arguments));
}

namespace Details {

template<typename TOut>
void formatArgumentTo(TOut& out, FormatSpecification specification, FormatArgument argument)
{
    auto writeAll = [](TOut& out, StringView str) {
        for (char c : str)
        {
            out.write(c);
        }
    };

    StaticArray<char, 12> rawBuffer;
    Span<char> buffer{rawBuffer.data(), rawBuffer.size()};

    switch (argument.getType())
    {
    case FormatArgument::Type::Bool:
        writeAll(out, argument.asBool() ? "true" : "false");
        break;

    case FormatArgument::Type::Char:
        out.write(argument.asChar());
        break;

    case FormatArgument::Type::S8:
        writeAll(out, toStringView(argument.asS8(), buffer, specification.getDecimalBase(), specification.isUpperCase()));
        break;

    case FormatArgument::Type::S16:
        writeAll(out, toStringView(argument.asS16(), buffer, specification.getDecimalBase(), specification.isUpperCase()));
        break;

    case FormatArgument::Type::S32:
        writeAll(out, toStringView(argument.asS32(), buffer, specification.getDecimalBase(), specification.isUpperCase()));
        break;

    case FormatArgument::Type::S64:
        writeAll(out, toStringView(argument.asS64(), buffer, specification.getDecimalBase(), specification.isUpperCase()));
        break;

    case FormatArgument::Type::U8:
        writeAll(out, toStringView(argument.asU8(), buffer, specification.getDecimalBase(), specification.isUpperCase()));
        break;

    case FormatArgument::Type::U16:
        writeAll(out, toStringView(argument.asU16(), buffer, specification.getDecimalBase(), specification.isUpperCase()));
        break;

    case FormatArgument::Type::U32:
        writeAll(out, toStringView(argument.asU32(), buffer, specification.getDecimalBase(), specification.isUpperCase()));
        break;

    case FormatArgument::Type::U64:
        writeAll(out, toStringView(argument.asU64(), buffer, specification.getDecimalBase(), specification.isUpperCase()));
        break;

    case FormatArgument::Type::String:
        for (char c : argument.asString())
        {
            out.write(c);
        }
        break;
    }
}

} // namespace Details

template<typename TOut>
void formatTo(TOut& out, StringView fmt, Span<FormatArgument> arguments)
{
    size_t nextArgumentIndex = 0;

    const size_t last = fmt.size() - 1;
    for (size_t i = 0; i < fmt.size(); ++i)
    {
        char c = fmt[i];

        if (c != '{')
        {
            out.write(c);
        }
        else // format expression
        {
            NOS_ASSERT(i != last, "Invalid format");

            ++i;

            // parse arg index
            if (isDigit(fmt[i]))
            {
                nextArgumentIndex = 0;
                do {
                    nextArgumentIndex = nextArgumentIndex * 10 + toDigit(fmt[i]);
                } while (++i < fmt.size() && isDigit(fmt[i]));
            }

            FormatSpecification specification;

            // parse format specification
            if (fmt[i] == ':')
            {
                ++i;
                NOS_ASSERT(i != last, "Invalid format");

                if (fmt[i] == '#')
                {
                    specification.alternativeForm = FormatSpecification::AlternativeForm::Yes;
                    ++i;
                    NOS_ASSERT(i != last, "Invalid format");
                }

                switch (fmt[i])
                {
                case 'b':
                    specification.presentation = FormatSpecification::Presentation::Binary;
                    break;

                case 'B':
                    specification.presentation = FormatSpecification::Presentation::BinaryUpperCase;
                    break;

                case 'c':
                    specification.presentation = FormatSpecification::Presentation::Character;
                    break;

                case 'd':
                    specification.presentation = FormatSpecification::Presentation::Decimal;
                    break;

                case 'o':
                    specification.presentation = FormatSpecification::Presentation::Octal;
                    break;

                case 'x':
                    specification.presentation = FormatSpecification::Presentation::Hexadecimal;
                    break;

                case 'X':
                    specification.presentation = FormatSpecification::Presentation::HexadecimalUpperCase;
                    break;

                default:
                    NOS_ASSERT(false, "Invalid format");
                    break;
                }

                ++i;
                NOS_ASSERT(i != last, "Invalid format");
            }

            // we should be at the end, otherwise the format is invalid
            NOS_ASSERT(fmt[i] == '}', "Invalid format");

            Details::formatArgumentTo(out, specification, arguments[nextArgumentIndex++]);
        }
    }
}

} // namespace NOS
