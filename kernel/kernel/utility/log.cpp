#include <kernel/utility/log.hpp>

#include <kernel/drivers/serial.hpp>
#include <nxx/string/format-to.hpp>

namespace nos::log {
namespace {

auto current_output = output::none;
bool is_output_enabled(output out)
{
    return (current_output & out) != output::none;
}

} // namespace

void set_output(output out)
{
    current_output = out;
}

void prints(string_view str)
{
    if (is_output_enabled(output::serial))
    {
        for (char c : str)
        {
            serial::write(c);
        }
    }
}

void printc(char c)
{
    if (is_output_enabled(output::serial))
    {
        serial::write(c);
    }
}

void vprint(string_view fmt, span<format_argument> args)
{
    if (is_output_enabled(output::serial))
    {
        struct
        {
            void write(char c)
            {
                serial::write(c);
            }
        } out;
        vformat_to(out, fmt, args);
    }
}

} // namespace nos::log
