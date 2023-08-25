#pragma once

#include <ncxx/utility/enum-string.hpp>

namespace NOS::Log {

enum class Level
{
    Unset = 0,
    Trace,
    Debug,
    Info,
    Warn,
    Error,
    Fatal,

    Disable,

    Count
};

inline constexpr EnumString<Level, Level::Count> LevelString;

} // namespace NOS::Log
