#pragma once

namespace NOS {

struct FormatSpecification
{
    enum class Presentation
    {
        Unset,

        Binary,
        BinaryUpperCase,

        Character,
        Decimal,
        Octal,

        Hexadecimal,
        HexadecimalUpperCase
    };

    enum class AlternativeForm
    {
        No,
        Yes
    };

    constexpr bool isUpperCase() const;
    constexpr auto getDecimalBase() const;

    Presentation presentation{Presentation::Unset};
    AlternativeForm alternativeForm : 1 {AlternativeForm::No};
};

constexpr bool FormatSpecification::isUpperCase() const
{
    return presentation == Presentation::BinaryUpperCase || presentation == Presentation::HexadecimalUpperCase;
}

constexpr auto FormatSpecification::getDecimalBase() const
{
    switch (presentation)
    {
    case Presentation::Binary:
    case Presentation::BinaryUpperCase:
        return 2;

    case Presentation::Character:
    case Presentation::Decimal:
    case Presentation::Unset:
        return 10;

    case Presentation::Octal:
        return 8;

    case Presentation::Hexadecimal:
    case Presentation::HexadecimalUpperCase:
        return 16;
    }

    NOS_ASSERT(false);
}

} // namespace NOS
