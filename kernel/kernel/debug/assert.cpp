#include <ncxx/debug/assert.hpp>

#include <kernel/utility/panic.hpp>

namespace NOS::Debug::Assert {

void triggerFailure(StringView condition, StringView message, SourceLocation location)
{
    panic(message.isEmpty() ? condition : message, location);
}

} // namespace NOS::Debug::Assert
