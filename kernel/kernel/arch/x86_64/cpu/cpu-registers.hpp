#pragma once

#include <kernel/def.hpp>

namespace nos::x86_64 {

struct NOS_PACKED cpu_registers
{
    u64_t r15, r14, r13, r12, r11, r10, r9, r8;
    u64_t rbp, rdi, rsi, rdx, rcx, rbx, rax;
    u64_t interrupt, error_code, rip, cs, rflags, rsp, ss;
};

}
