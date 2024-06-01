#pragma once

#include <kernel/def.hpp>
#include <kernel/utility/log_level.hpp>
#include <kernel/utility/logger.hpp>
#include <nxx/container/span.hpp>
#include <nxx/memory/allocator/stack_allocator.hpp>
#include <nxx/memory/construct_at.hpp>
#include <nxx/string/format_argument.hpp>
#include <nxx/string/string_view.hpp>

namespace nos::log::details {

class main_logger
{
public:
    static main_logger& get();

public:
    main_logger() = default;
    ~main_logger();

    template<typename LoggerT, typename... ArgsT>
    LoggerT& add_logger(ArgsT&&... args);

    void vlog(log_level level, string_view fmt, span<format_argument> args);

    void set_level(log_level level) { _logger_level = level; }

private:
    struct logger_node
    {
        logger* logger;
        logger_node* next_logger_node{nullptr};
    };

    template<typename LoggerT>
    struct inplace_logger_node : logger_node
    {
        inplace_logger_node();

        template<typename... ArgsT>
        inplace_logger_node(ArgsT&&... args);

        LoggerT inplace_logger;
    };

private:
    void* allocate_logger(size_t size);
    void link_logger(logger_node& logger);

private:
    stack_allocator<NOS_MAIN_LOGGER_STACK_ALLOCATOR_SIZE> _allocator{};

    logger_node* _first_logger_node{nullptr};

    log_level _logger_level{log_level::trace};
};

template<typename LoggerT>
main_logger::inplace_logger_node<LoggerT>::inplace_logger_node()
{
    logger = &inplace_logger;
}

template<typename LoggerT>
template<typename... ArgsT>
main_logger::inplace_logger_node<LoggerT>::inplace_logger_node(ArgsT&&... args)
    : inplace_logger(forward<ArgsT>(args)...)
{
    logger = &inplace_logger;
}

template<typename LoggerT, typename... ArgsT>
LoggerT& main_logger::add_logger(ArgsT&&... args)
{
    inplace_logger_node<LoggerT>* node = construct_at(static_cast<inplace_logger_node<LoggerT>*>(allocate_logger(sizeof(inplace_logger_node<LoggerT>))), forward<ArgsT>(args)...);
    link_logger(*node);
    return node->inplace_logger;
}

} // namespace nos::log::details
