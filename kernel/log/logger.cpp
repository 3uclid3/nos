#include <lib/logging/logger.hpp>

#include <span>

#include <lib/logging/message.hpp>

namespace nos::log {

namespace {

class local_buffers
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

struct printer
{
    constexpr printer& operator=(char c)
    {
        buffer[size++] = c;
        return *this;
    }

    constexpr printer& operator*() { return *this; }
    constexpr printer& operator++() { return *this; }
    constexpr printer& operator++(int) { return *this; }

    std::span<char> buffer;
    std::size_t size{0};
};

// TODO thread_local
local_buffers buffers;

} // namespace

std::string_view vformat(std::string_view fmt, std::format_args args)
{
    printer out{.buffer = buffers.next_buffer()};
    out = std::vformat_to(out, fmt, args);
    return std::string_view{out.buffer.data(), out.size};
}

logger& logger::get()
{
    // ensure that the logger is initialized before global constructors are called
    static logger instance;
    return instance;
}

logger::~logger()
{
    for (sink_node* sink_node = _first_sink_node; sink_node != nullptr; sink_node = sink_node->next_node)
    {
        std::destroy_at(sink_node);
    }
}

void logger::vlog(level level, std::string_view fmt, std::format_args args)
{
    if (level >= _level)
    {
        message message{
            .level = level,
            .string = args.max_size() == 0 ? fmt : vformat(fmt, args)};

        for (sink_node* sink_node = _first_sink_node; sink_node != nullptr; sink_node = sink_node->next_node)
        {
            sink_node->sink->log(message);
        }
    }
}

void* logger::allocate_sink(size_t size)
{
    return _allocator.allocate(size).ptr;
}

void logger::link_sink(sink_node& sink)
{
    if (_first_sink_node == nullptr)
    {
        _first_sink_node = &sink;
    }
    else
    {
        auto* sink_node = _first_sink_node;

        while (sink_node->next_node != nullptr)
        {
            sink_node = sink_node->next_node;
        }
        sink_node->next_node = &sink;
    }
}

} // namespace nos::log
