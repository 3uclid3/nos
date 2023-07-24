#pragma once

#include <string/string-view.hpp>
#include <utility/source-location.hpp>

namespace NOS::Debug::Assert {

void triggerFailure(StringView condition, StringView message, SourceLocation location = SourceLocation::current());

} // namespace NOS::Debug::Assert

#define _NOS_ASSERT_MSG(condition, message) \
    do { \
        if (!(condition)) NOS::Debug::Assert::triggerFailure(#condition, message); \
    } while (false)

#define _NOS_ASSERT_NO_MSG(condition) \
    do { \
        if (!(condition)) NOS::Debug::Assert::triggerFailure(#condition, {}); \
    } while (false)

#define _NOS_ASSERT_MSG_OR_NO_MSG_SELECTOR(a, b, assertMacro, ...) assertMacro
#define NOS_ASSERT(...) _NOS_ASSERT_MSG_OR_NO_MSG_SELECTOR(__VA_ARGS__, _NOS_ASSERT_MSG, _NOS_ASSERT_NO_MSG)(__VA_ARGS__)
