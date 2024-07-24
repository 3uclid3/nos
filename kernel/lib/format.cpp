#include <lib/format.hpp>

#include <array>
#include <cassert>
#include <span>

namespace nos {

namespace {

class format_printer_buffers
{
public:
    static constexpr std::size_t buffer_size = 8192;
    static constexpr std::size_t buffer_count = 16;
    static constexpr std::size_t last_buffer_index = buffer_count - 1;

    std::span<char> next_buffer()
    {
        const size_t offset = _next_buffer_index * buffer_size;
        _next_buffer_index = _next_buffer_index == last_buffer_index ? 0 : _next_buffer_index + 1;
        return {&_buffer[offset], buffer_size};
    }

private:
    std::array<char, buffer_size * buffer_count> _buffer;
    std::size_t _next_buffer_index{0};
};

struct format_printer
{
    constexpr format_printer& operator=(char c)
    {
        assert(count < buffer.size());
        buffer[count++] = c;
        return *this;
    }

    constexpr format_printer& operator*() { return *this; }
    constexpr format_printer& operator++() { return *this; }
    constexpr format_printer& operator++(int) { return *this; }

    std::span<char> buffer;
    std::size_t count{0};
};

// TODO thread_local
format_printer_buffers printer_buffers;

} // namespace

std::string_view vformat_sv(std::string_view fmt, std::format_args args)
{
    format_printer printer{.buffer = printer_buffers.next_buffer()};
    printer = std::vformat_to(printer, fmt, args);
    return std::string_view{printer.buffer.data(), printer.count};
}

} // namespace nos
