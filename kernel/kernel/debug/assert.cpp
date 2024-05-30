#include <kernel/debug/assert.hpp>

#include <kernel/arch/arch.hpp>
#include <kernel/utility/log.hpp>

namespace nxx::details {

void trigger_assert(const char* condition, const char* message, const char* file, size_t line)
{
    nos::log::fatalln("Assertion failed: {}", condition);
    nos::log::fatalln("File: {}", file);
    nos::log::fatalln("Line: {}", file);

    if (message != nullptr && message[0] != '\0')
    {
        nos::log::fatalln(message);
    }

    nos::log::fatalln("System halted");

    nos::arch::halt(false);
}

} // namespace nxx::details