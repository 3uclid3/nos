#pragma once

#define NOS_ENABLE_LOG 1

#ifndef NOS_DEFAULT_ARRAY_ALLOCATOR
#include <ncxx/memory/allocator/malloc-allocator.hpp>
#define NOS_DEFAULT_ARRAY_ALLOCATOR NOS::Memory::MallocAllocator
#endif