#pragma once

#include <ncxx/basic-types.hpp>

namespace NOS::X86_64::GDT {

namespace Selector {

inline constexpr u8_t Null = 0x00;
inline constexpr u8_t Code = 0x08;
inline constexpr u8_t Data = 0x10;
inline constexpr u8_t UserCode = 0x18;
inline constexpr u8_t UserData = 0x20;
inline constexpr u8_t TSS = 0x28;

} // namespace Selector

void initialize();

} // namespace NOS::X86_64::GDT