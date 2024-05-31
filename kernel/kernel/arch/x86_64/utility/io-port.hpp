#pragma once

#include <kernel/def.hpp>

namespace nos {

template<typename T>
class io_port;

class base_io_port
{
public:
    constexpr base_io_port() = default;
    constexpr base_io_port(u16_t port);

    [[nodiscard]] constexpr u16_t get_port() const;

protected:
    u16_t _port{};
};

template<>
class io_port<u8_t> : public base_io_port
{
public:
    constexpr io_port() = default;
    constexpr io_port(u16_t port);

    u8_t read(u16_t offset = 0);
    void write(u8_t data, u16_t offset = 0);
};

template<>
class io_port<u16_t> : public base_io_port
{
public:
    constexpr io_port() = default;
    constexpr io_port(u16_t port);

    u16_t read(u16_t offset = 0);
    void write(u16_t data, u16_t offset = 0);
};

template<>
class io_port<u32_t> : public base_io_port
{
public:
    constexpr io_port() = default;
    constexpr io_port(u16_t port);

    u32_t read(u16_t offset = 0);
    void write(u32_t data, u16_t offset = 0);
};

constexpr base_io_port::base_io_port(u16_t port)
    : _port(port)
{}

constexpr u16_t base_io_port::get_port() const
{
    return _port;
}

constexpr io_port<u8_t>::io_port(u16_t port)
    : base_io_port(port)
{}

inline u8_t io_port<u8_t>::read(u16_t offset)
{
    u8_t data{};
    asm volatile("inb %w1, %b0" : "=a"(data) : "Nd"(_port + offset));
    return data;
}

inline void io_port<u8_t>::write(u8_t data, u16_t offset)
{
    asm volatile("outb %b0, %w1" ::"a"(data), "Nd"(_port + offset));
}

constexpr io_port<u16_t>::io_port(u16_t port)
    : base_io_port(port)
{}

inline u16_t io_port<u16_t>::read(u16_t offset)
{
    u16_t data{};
    asm volatile("inw %w1, %w0" : "=a"(data) : "Nd"(_port + offset));
    return data;
}

inline void io_port<u16_t>::write(u16_t data, u16_t offset)
{
    asm volatile("outw %b0, %w1" ::"a"(data), "Nd"(_port + offset));
}

constexpr io_port<u32_t>::io_port(u16_t port)
    : base_io_port(port)
{}

inline u32_t io_port<u32_t>::read(u16_t offset)
{
    u32_t data{};
    asm volatile("inl %w1, %w0" : "=a"(data) : "Nd"(_port + offset));
    return data;
}

inline void io_port<u32_t>::write(u32_t data, u16_t offset)
{
    asm volatile("outl %b0, %w1" ::"a"(data), "Nd"(_port + offset));
}

} // namespace nos
