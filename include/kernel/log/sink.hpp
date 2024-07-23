#pragma once

#include <hedley/hedley.h>

namespace nos::log {

struct message;

class sink
{
public:
    virtual ~sink() = default;

    void log(const message& message);

private:
    virtual void log_impl(const message& message) = 0;
};

HEDLEY_INLINE void sink::log(const message& message)
{
    log_impl(message);
}
} // namespace nos::log
