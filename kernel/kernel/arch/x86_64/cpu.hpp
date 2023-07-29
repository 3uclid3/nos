#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/preprocessor/packed.hpp>

namespace NOS::X86_64::CPU {

struct NOS_PACKED Registers
{
    u64_t r15, r14, r13, r12, r11, r10, r9, r8;
    u64_t rbp, rdi, rsi, rdx, rcx, rbx, rax;
    u64_t interrupt, errorCode, rip, cs, rflags, rsp, ss;
};

inline void pause()
{
    asm volatile("pause");
}

} // namespace NOS::X86_64::CPU
