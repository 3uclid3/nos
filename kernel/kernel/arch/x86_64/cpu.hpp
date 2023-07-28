#pragma once

namespace NOS::X86_64::CPU {

inline void pause()
{
    asm volatile("pause");
}

} // namespace NOS::X86_64::CPU
