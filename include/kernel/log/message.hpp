#pragma once

#include <string_view>

#include <log/level.hpp>

namespace nos::log {

struct message
{
    level level;
    std::string_view string;

    // TODO tid, timestamp
};

} // namespace nos::log