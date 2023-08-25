#pragma once

#include <ncxx/basic-types.hpp>

namespace NOS::Memory {

struct Block;

Block allocate(size_t size);
Block reallocate(Block block, size_t size);
void deallocate(Block block);

} // namespace NOS::Memory
