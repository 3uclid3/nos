#include <kernel/utility/log.hpp>

#include <nxx/string/format-to.hpp>

namespace nos::log {
namespace {

// TODO ref_wrap
printer* main_printer{nullptr};

} // namespace

void set_printer(printer& printer)
{
    main_printer = &printer;
}

void unset_printer()
{
    main_printer = nullptr;
}

void prints(string_view str)
{
    if (main_printer)
    {
        main_printer->prints(str);
    }
}

void printc(char c)
{
    if (main_printer)
    {
        main_printer->printc(c);
    }
}

void vprint(string_view fmt, span<format_argument> args)
{
    if (main_printer)
    {
        struct
        {
            void write(char c)
            {
                main_printer->printc(c);
            }
        } out;

        vformat_to(out, fmt, args);
    }
}

} // namespace nos::log
