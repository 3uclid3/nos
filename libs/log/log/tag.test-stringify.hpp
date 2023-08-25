#pragma once

#include <log/tag.hpp>

namespace Catch {
template<>
struct StringMaker<NOS::Log::Tag>
{
    static std::string convert(const NOS::Log::Tag& tag)
    {
        return std::string(tag.name.data(), tag.name.size());
    }
};
} // namespace Catch