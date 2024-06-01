#include <kernel/debug/assert.hpp>

#include <kernel/arch/arch.hpp>
#include <kernel/utility/log.hpp>

namespace nxx::details {

void trigger_assert(const char* condition, const char* message, const char* file, size_t line)
{
    using namespace nos;

    log::fatal("Assertion failed: {}", condition);
    log::fatal("File: {}", file);
    log::fatal("Line: {}", file);

    if (message != nullptr && message[0] != '\0')
    {
        log::fatal(message);
    }

    log::fatal("System halted");

    arch::halt(false);
}

} // namespace nxx::details
