#pragma once

#include <cstdint>

#include <kdef.hpp>

namespace nos {

template<typename T>
class io_port;

class base_io_port
{
public:
    constexpr base_io_port() = default;
    constexpr base_io_port(std::uint16_t port);

    [[nodiscard]] constexpr std::uint16_t get_port() const;

protected:
    std::uint16_t _port{};
};

template<>
class io_port<std::uint8_t> : public base_io_port
{
public:
    constexpr io_port() = default;
    constexpr io_port(std::uint16_t port);

    [[nodiscard]] std::uint8_t read(std::uint16_t offset = 0);
    void write(std::uint8_t data, std::uint16_t offset = 0);
};

template<>
class io_port<std::uint16_t> : public base_io_port
{
public:
    constexpr io_port() = default;
    constexpr io_port(std::uint16_t port);

    [[nodiscard]] std::uint16_t read(std::uint16_t offset = 0);
    void write(std::uint16_t data, std::uint16_t offset = 0);
};

template<>
class io_port<std::uint32_t> : public base_io_port
{
public:
    constexpr io_port() = default;
    constexpr io_port(std::uint16_t port);

    [[nodiscard]] std::uint32_t read(std::uint16_t offset = 0);
    void write(std::uint32_t data, std::uint16_t offset = 0);
};

constexpr base_io_port::base_io_port(std::uint16_t port)
    : _port(port)
{}

constexpr std::uint16_t base_io_port::get_port() const
{
    return _port;
}

constexpr io_port<std::uint8_t>::io_port(std::uint16_t port)
    : base_io_port(port)
{}

inline std::uint8_t io_port<std::uint8_t>::read(std::uint16_t offset)
{
    std::uint8_t data{};
    asm volatile("inb %w1, %b0" : "=a"(data) : "Nd"(_port + offset));
    return data;
}

inline void io_port<std::uint8_t>::write(std::uint8_t data, std::uint16_t offset)
{
    asm volatile("outb %b0, %w1" ::"a"(data), "Nd"(_port + offset));
}

constexpr io_port<std::uint16_t>::io_port(std::uint16_t port)
    : base_io_port(port)
{}

inline std::uint16_t io_port<std::uint16_t>::read(std::uint16_t offset)
{
    std::uint16_t data{};
    asm volatile("inw %w1, %w0" : "=a"(data) : "Nd"(_port + offset));
    return data;
}

inline void io_port<std::uint16_t>::write(std::uint16_t data, std::uint16_t offset)
{
    asm volatile("outw %b0, %w1" ::"a"(data), "Nd"(_port + offset));
}

constexpr io_port<std::uint32_t>::io_port(std::uint16_t port)
    : base_io_port(port)
{}

inline std::uint32_t io_port<std::uint32_t>::read(std::uint16_t offset)
{
    std::uint32_t data{};
    asm volatile("inl %w1, %w0" : "=a"(data) : "Nd"(_port + offset));
    return data;
}

inline void io_port<std::uint32_t>::write(std::uint32_t data, std::uint16_t offset)
{
    asm volatile("outl %b0, %w1" ::"a"(data), "Nd"(_port + offset));
}

} // namespace nos