#include <catch2/catch_test_macros.hpp>

#include <log/log.hpp>
#include <log/message.hpp>
#include <log/sink.hpp>
#include <ncxx/container/array.hpp>

namespace NOS::Log {

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

    TestSink* _sink;
};

TEST_CASE_METHOD(Fixture, "Trace", "[Log]")
{
    expectedMessage(Level::Trace, TagOf<Fixture>, "Trace message");

    trace<Fixture>("Trace message");

    checkReceivedExpectedMessages();
}

TEST_CASE_METHOD(Fixture, "Debug", "[Log]")
{
    expectedMessage(Level::Debug, TagOf<Fixture>, "Debug message");

    debug<Fixture>("Debug message");

    checkReceivedExpectedMessages();
}

TEST_CASE_METHOD(Fixture, "Info", "[Log]")
{
    expectedMessage(Level::Info, TagOf<Fixture>, "Info message");

    info<Fixture>("Info message");

    checkReceivedExpectedMessages();
}

TEST_CASE_METHOD(Fixture, "Warn", "[Log]")
{
    expectedMessage(Level::Warn, TagOf<Fixture>, "Warn message");

    warn<Fixture>("Warn message");

    checkReceivedExpectedMessages();
}

TEST_CASE_METHOD(Fixture, "Error", "[Log]")
{
    expectedMessage(Level::Error, TagOf<Fixture>, "Error message");

    error<Fixture>("Error message");

    checkReceivedExpectedMessages();
}

TEST_CASE_METHOD(Fixture, "Fatal", "[Log]")
{
    expectedMessage(Level::Fatal, TagOf<Fixture>, "Fatal message");

    fatal<Fixture>("Fatal message");

    checkReceivedExpectedMessages();
}

} // namespace NOS::Log
