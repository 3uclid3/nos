#include <lib/log.hpp>

#include <lib/format.hpp>

namespace nos::log {

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
            .string = args.max_size() == 0 ? fmt : vformat_sv(fmt, args)};

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
