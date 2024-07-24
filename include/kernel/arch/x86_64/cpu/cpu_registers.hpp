#pragma once

#include <cstdint>

#include <kdef.hpp>

namespace nos::x86_64 {

struct NOS_PACKED cpu_registers
{
    std::uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    std::uint64_t rbp, rdi, rsi, rdx, rcx, rbx, rax;
    std::uint64_t interrupt, error_code, rip, cs, rflags, rsp, ss;
};

} // namespace nos::x86_64
