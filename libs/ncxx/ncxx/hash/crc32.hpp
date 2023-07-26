#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/hash/details/crc32-table.hpp>
#include <ncxx/string/string-view.hpp>

namespace NOS {

constexpr u32_t crc32(StringView string, u32_t crc = 0u)
{
    crc = crc ^ 0xFFFFFFFFu;
    for (char c : string)
    {
        crc = Details::Crc32Table[static_cast<u32_t>(c) ^ (crc & 0xFF)] ^ (crc >> 8);
    }
    crc = crc ^ 0xFFFFFFFFu;
    return crc;
}

} // namespace NOS
