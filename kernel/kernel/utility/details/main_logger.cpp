#include <kernel/utility/details/main_logger.hpp>

#include <nxx/string/format.hpp>

namespace nos::log::details {

main_logger& main_logger::get()
{
    // ensure that the logger is initialized before global constructors are called
    static main_logger logger;
    return logger;
}

main_logger::~main_logger()
{
    for (logger_node* logger = _first_logger_node; logger != nullptr; logger = logger->next_logger_node)
    {
        destroy_at(logger);
    }
}

void main_logger::vlog(log_level level, string_view fmt, span<format_argument> args)
{
    if (level >= _logger_level)
    {
        string_view message = vformat(fmt, args);

        for (logger_node* logger_node = _first_logger_node; logger_node != nullptr; logger_node = logger_node->next_logger_node)
        {
            logger_node->logger->log(message);
        }
    }
}

void* main_logger::allocate_logger(size_t size)
{
    return _allocator.allocate(size).pointer;
}

void main_logger::link_logger(logger_node& logger)
{
    if (_first_logger_node == nullptr)
    {
        _first_logger_node = &logger;
    }
    else
    {
        auto* logger_node = _first_logger_node;;
        while(logger_node->next_logger_node != nullptr)
        {
            logger_node = logger_node->next_logger_node;
        }
        logger_node->next_logger_node = &logger;
    }
}

} // namespace nos::log::details
