#pragma once

#include <format>
#include <memory>
#include <string_view>
#include <utility>

#include <ca/stack_allocator.hpp>

#include <lib/logging/level.hpp>
#include <lib/logging/sink.hpp>

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

    void vlog(level level, std::string_view fmt, std::format_args args);

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
    ca::stack_allocator<64> _allocator{};

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
    inplace_sink_node<SinkT>* node = std::construct_at(static_cast<inplace_sink_node<SinkT>*>(allocate_sink(sizeof(inplace_sink_node<SinkT>))), std::forward<ArgsT>(args)...);
    link_sink(*node);
    return node->inplace_sink;
}

} // namespace nos::log
