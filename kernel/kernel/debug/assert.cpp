#include <kernel/debug/assert.hpp>

#include <kernel/arch.hpp>
#include <kernel/log.hpp>

namespace nxx::details {

void trigger_assert(const char* condition, const char* message, const char* file, size_t line)
{
    using namespace nos;

    log::fatal("Assertion failed: {}", condition);
    log::fatal("File: {}", file);
    log::fatal("Line: {}", line);

    if (message != nullptr && message[0] != '\0')
    {
        log::fatal(message);
    }

    log::fatal("System halted");

    arch::hcf();
}

} // namespace nxx::details
