#pragma once

#include <nxx/string/string-view.hpp>

namespace nos {

class logger
{
public:
    virtual ~logger() = default;

    void log(string_view str) { log_impl(str); }

private:
    virtual void log_impl(string_view str) = 0;
};

} // namespace nos
