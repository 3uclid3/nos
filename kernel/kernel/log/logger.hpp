#pragma once

#include <kernel/def.hpp>
#include <kernel/log/level.hpp>
#include <kernel/log/sink.hpp>
#include <nxx/container/span.hpp>
#include <nxx/memory/allocator/stack_allocator.hpp>
#include <nxx/memory/construct_at.hpp>
#include <nxx/string/format_argument.hpp>
#include <nxx/string/string_view.hpp>

namespace nos::log {

class logger
{
public:
    static logger& get();

public:
    logger() = default;
    ~logger();

    template<typename SinkT, typename... ArgsT>
    SinkT& add_sink(ArgsT&&... args);

    void vlog(level level, string_view fmt, span<format_argument> args);

    void set_level(level level) { _level = level; }

private:
    struct sink_node
    {
        sink* sink;
        sink_node* next_node{nullptr};
    };

    template<typename SinkT>
    struct inplace_sink_node : sink_node
    {
        inplace_sink_node();

        template<typename... ArgsT>
        inplace_sink_node(ArgsT&&... args);

        SinkT inplace_sink;
    };

private:
    void* allocate_sink(size_t size);
    void link_sink(sink_node& sink);

private:
    stack_allocator<logger_stack_allocator_size> _allocator{};

    sink_node* _first_sink_node{nullptr};

    level _level{level::trace};
};

template<typename SinkT>
logger::inplace_sink_node<SinkT>::inplace_sink_node()
{
    sink = &inplace_sink;
}

template<typename SinkT>
template<typename... ArgsT>
logger::inplace_sink_node<SinkT>::inplace_sink_node(ArgsT&&... args)
    : inplace_sink(forward<ArgsT>(args)...)
{
    sink = &inplace_sink;
}

template<typename SinkT, typename... ArgsT>
SinkT& logger::add_sink(ArgsT&&... args)
{
    inplace_sink_node<SinkT>* node = construct_at(static_cast<inplace_sink_node<SinkT>*>(allocate_sink(sizeof(inplace_sink_node<SinkT>))), forward<ArgsT>(args)...);
    link_sink(*node);
    return node->inplace_sink;
}

} // namespace nos::log
