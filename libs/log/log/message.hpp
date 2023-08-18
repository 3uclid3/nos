#pragma once

#include <log/level.hpp>
#include <log/tag.hpp>
#include <ncxx/string/string-view.hpp>
#include <ncxx/utility/source-location.hpp>

namespace NOS::Log {

struct Message
{
    SourceLocation sourceLocation;
    StringView message;
    Tag tag;
    Level level;

    // TODO Thread
    // TODO Time
};

} // namespace NOS::Log