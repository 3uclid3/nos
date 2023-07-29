#pragma once

#include <ncxx/build-type.hpp>

#define NOS_ARCH_X86_64 1

#if NOS_ARCH_X86_64
#define NOS_KERNEL_ARCH_TYPE(className) NOS::X86_64::className
#define NOS_KERNEL_ARCH_FOLDER x86_64
#endif

#define NOS_INCLUDE_KERNEL_ARCH_FILE(fileName) <kernel/arch/NOS_KERNEL_ARCH_FOLDER/fileName>
