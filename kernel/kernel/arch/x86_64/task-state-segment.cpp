#include <kernel/arch/x86_64/task-state-segment.hpp>

namespace NOS {

void TaskStateSegment::Entry::setPointer(const TaskStateSegment& tss)
{
    const uintptr_t ptr = reinterpret_cast<uintptr_t>(&tss);

    base0 = static_cast<u16_t>(ptr);
    base1 = static_cast<u8_t>(ptr >> 16);
    base2 = static_cast<u8_t>(ptr >> 24);
    base3 = static_cast<u32_t>(ptr >> 32);
}

} // namespace NOS