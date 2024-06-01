#pragma once

#include <kernel/def.hpp>
#include <kernel/log/level.hpp>
#include <nxx/string/string_view.hpp>

namespace nos::log {

struct message
{
    level level;
    string_view string;

    // TODO tid, timestamp
};

} // namespace nos::log
