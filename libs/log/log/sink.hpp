#pragma once

#include <ncxx/functional/function.hpp>

namespace NOS::Log {

struct Message;

class Sink
{
public:
    virtual ~Sink() = default;

    void log(const Message& message) { logImpl(message); }

private:
    virtual void logImpl(const Message& message) = 0;
};

} // namespace NOS::Log
