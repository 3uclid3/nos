#pragma once

#include <log/sink.hpp>

namespace NOS::Log {

class SerialSink : public Sink
{
private:
    void logImpl(const Message& message) override;
};

} // namespace NOS::Log