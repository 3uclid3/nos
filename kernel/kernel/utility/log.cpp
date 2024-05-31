#include <kernel/utility/log.hpp>

#include <nxx/string/format-to.hpp>

namespace nos::log {
namespace details {

printer* printer{nullptr};

} // namespace details

void printer::prints(string_view str)
{
    prints_impl(str);

    if (_next_printer)
    {
        _next_printer->prints(str);
    }
}

void printer::printc(char c)
{
    printc_impl(c);

    if (_next_printer)
    {
        _next_printer->printc(c);
    }
}

void add_printer(printer& printer)
{
    if (details::printer)
    {
        printer._next_printer = details::printer;
    }

    details::printer = &printer;
}

void prints(string_view str)
{
    if (details::printer)
    {
        details::printer->prints(str);
    }
}

void printc(char c)
{
    if (details::printer)
    {
        details::printer->printc(c);
    }
}

void vprint(string_view fmt, span<format_argument> args)
{
    if (details::printer)
    {
        struct
        {
            void write(char c)
            {
                details::printer->printc(c);
            }
        } out;

        vformat_to(out, fmt, args);
    }
}

} // namespace nos::log
