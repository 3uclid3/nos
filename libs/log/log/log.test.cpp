#include <catch2/catch_test_macros.hpp>

#include <log/log.hpp>
#include <log/message.hpp>
#include <log/sink.hpp>
#include <log/tag.test-stringify.hpp>
#include <ncxx/container/array.hpp>

namespace NOS::Log {

struct TestTag
{};

class TestSink : public Sink
{
public:
    void expectedMessage(Level level, Tag tag, StringView message)
    {
        _expectedMessages.emplaceLast(Message{
            .message = message,
            .tag = tag,
            .level = level});
    }

    void logImpl(const Message& message) override
    {
        REQUIRE(_nextMessageIndex < _expectedMessages.size());

        CHECK(_expectedMessages[_nextMessageIndex].level == message.level);
        CHECK(_expectedMessages[_nextMessageIndex].message == message.message);
        CHECK(_expectedMessages[_nextMessageIndex].tag == message.tag);

        ++_nextMessageIndex;
    }

    Array<Message> _expectedMessages;
    size_t _nextMessageIndex{0};
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
        CHECK(_sink->_expectedMessages.size() == _sink->_nextMessageIndex);
    }

    template<typename TFunc>
    void checkLevel(Level level, TFunc func)
    {
        static constexpr StringView msg = "Message for level check";

        expectedMessage(level, TagOf<TestTag>, msg);
        expectedMessage(level, TagOf<TestTag>, msg);
        expectedMessage(level, TagOf<TestTag>, msg);

        func(msg);

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
        checkLevel(Level::Trace, [this](StringView msg) {
            trace<TestTag>(msg);
            trace(_tag, msg);
            trace(_tagPtr, msg);
        });
    }

    SECTION("Debug")
    {
        checkLevel(Level::Debug, [this](StringView msg) {
            debug<TestTag>(msg);
            debug(_tag, msg);
            debug(_tagPtr, msg);
        });
    }

    SECTION("Info")
    {
        checkLevel(Level::Info, [this](StringView msg) {
            info<TestTag>(msg);
            info(_tag, msg);
            info(_tagPtr, msg);
        });
    }

    SECTION("Warn")
    {
        checkLevel(Level::Warn, [this](StringView msg) {
            warn<TestTag>(msg);
            warn(_tag, msg);
            warn(_tagPtr, msg);
        });
    }

    SECTION("Error")
    {
        checkLevel(Level::Error, [this](StringView msg) {
            error<TestTag>(msg);
            error(_tag, msg);
            error(_tagPtr, msg);
        });
    }

    SECTION("Fatal")
    {
        checkLevel(Level::Fatal, [this](StringView msg) {
            fatal<TestTag>(msg);
            fatal(_tag, msg);
            fatal(_tagPtr, msg);
        });
    }

    SECTION("Disable")
    {
        auto logAll = [this] {
            trace(_tag, "Disable");
            debug(_tag, "Disable");
            info(_tag, "Disable");
            warn(_tag, "Disable");
            error(_tag, "Disable");
            fatal(_tag, "Disable");
        };

        SECTION("global")
        {
            setLevel(Level::Disable);

            logAll();

            CHECK(_sink->_nextMessageIndex == 0);
        }

        SECTION("tag")
        {
            setLevel<TestTag>(Level::Disable);

            logAll();

            CHECK(_sink->_nextMessageIndex == 0);
        }
    }
}

} // namespace NOS::Log
