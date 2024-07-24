#pragma once

#include <string_view>

#include <lib/logging/level.hpp>

namespace nos::log {

struct message
{
    level level;
    std::string_view string;

    // TODO tid, timestamp
};

} // namespace nos::log