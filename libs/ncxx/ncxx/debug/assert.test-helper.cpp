#include <ncxx/debug/assert.hpp>

#include <sstream>
#include <string>
#include <string_view>

#include <catch2/catch_test_macros.hpp>

#include <ncxx/preprocessor/unused.hpp>
#include <ncxx/string/string-view.hpp>
#include <ncxx/utility/source-location.hpp>

namespace NOS::Debug::Assert {

void triggerFailure(StringView condition, StringView message, SourceLocation location)
{
    std::string_view conditionStr{condition.data(), condition.size()};
    std::string_view messageStr{message.data(), message.size()};
    std::string_view fileNameStr{location.fileName().data(), location.fileName().size()};

    std::stringstream ss;
    ss << "Assert '" << conditionStr << "' failed.\n";
    if (!messageStr.empty())
    {
        ss << "\r\rwith message '" << messageStr << "'\n";
    }
    ss << "\t\t in " << fileNameStr << "(" << location.line() << ")\n";

    std::string string = ss.str();
    FAIL(string.c_str());
}

} // namespace NOS::Debug::Assert