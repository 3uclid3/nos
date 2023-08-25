#include <catch2/catch_test_macros.hpp>

#include <log/log.hpp>
#include <log/message.hpp>
#include <log/sink.hpp>
#include <log/tag.test-stringify.hpp>
#include <ncxx/container/array.hpp>
#include <ncxx/string/format.hpp>

namespace NOS::Log {

struct TestTag
{};

class TestSink : public Sink
{
public:
    void expectedMessage(Level level, Tag tag, StringView message)
    {
        _expected = Message{
            .message = message,
            .tag = tag,
            .level = level};
    }

    void logImpl(const Message& message) override
    {
        CHECK(message.level == _expected.level);
        CHECK(message.tag == _expected.tag);
        CHECK(message.message == _expected.message);

        _logged = true;
    }

    Message _expected;
    bool _logged{false};
};

struct Fixture
{
    Fixture()
    {
        setLevel(Level::Trace);

        auto sink = makeUnique<TestSink>();

        _sink = sink.get();

        addSink(move(sink));
    }

    ~Fixture()
    {
        clearSinks();
    }

    void expectedMessage(Level level, Tag tag, StringView message)
    {
        _sink->expectedMessage(level, tag, message);
    }

    void checkReceivedExpectedMessages()
    {
        CHECK(_sink->_logged);
    }

    template<typename TFunc>
    void checkLevel(Level level, TFunc func)
    {
        static constexpr StringView msg = "Message for level {} check";
        const StringView expectedMsg = format(msg, LevelString.string(level));

        expectedMessage(level, TagOf<TestTag>, expectedMsg);

        func(msg, LevelString.string(level));

        checkReceivedExpectedMessages();
    }

    TestTag _tag;
    TestTag* _tagPtr{&_tag};

    TestSink* _sink;
};

TEST_CASE_METHOD(Fixture, "Level", "[Log]")
{
    SECTION("Trace")
    {
        checkLevel(Level::Trace, [this](StringView fmt, StringView arg) {
            trace<TestTag>().format(fmt, arg);
            trace(_tag).format(fmt, arg);
            trace(_tagPtr).format(fmt, arg);
        });
    }
    SECTION("Debug")
    {
        checkLevel(Level::Debug, [this](StringView fmt, StringView arg) {
            debug<TestTag>().format(fmt, arg);
            debug(_tag).format(fmt, arg);
            debug(_tagPtr).format(fmt, arg);
        });
    }

    SECTION("Info")
    {
        checkLevel(Level::Info, [this](StringView fmt, StringView arg) {
            info<TestTag>().format(fmt, arg);
            info(_tag).format(fmt, arg);
            info(_tagPtr).format(fmt, arg);
        });
    }

    SECTION("Warn")
    {
        checkLevel(Level::Warn, [this](StringView fmt, StringView arg) {
            warn<TestTag>().format(fmt, arg);
            warn(_tag).format(fmt, arg);
            warn(_tagPtr).format(fmt, arg);
        });
    }

    SECTION("Error")
    {
        checkLevel(Level::Error, [this](StringView fmt, StringView arg) {
            error<TestTag>().format(fmt, arg);
            error(_tag).format(fmt, arg);
            error(_tagPtr).format(fmt, arg);
        });
    }

    SECTION("Fatal")
    {
        checkLevel(Level::Fatal, [this](StringView fmt, StringView arg) {
            fatal<TestTag>().format(fmt, arg);
            fatal(_tag).format(fmt, arg);
            fatal(_tagPtr).format(fmt, arg);
        });
    }

    SECTION("Disable")
    {
        auto logAll = [this] {
            trace(_tag).message("Disable");
            debug(_tag).message("Disable");
            info(_tag).message("Disable");
            warn(_tag).message("Disable");
            error(_tag).message("Disable");
            fatal(_tag).message("Disable");
        };

        SECTION("global")
        {
            setLevel(Level::Disable);

            logAll();

            CHECK_FALSE(_sink->_logged);
        }

        SECTION("tag")
        {
            setLevel<TestTag>(Level::Disable);

            logAll();

            CHECK_FALSE(_sink->_logged);
        }
    }
}

} // namespace NOS::Log
