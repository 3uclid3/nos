#pragma once

namespace nos::log {

struct message;

class sink
{
public:
    virtual ~sink() = default;

    void log(const message& message) { log_impl(message); }

private:
    virtual void log_impl(const message& message) = 0;
};

} // namespace nos::log
