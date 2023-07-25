#include <string/format.hpp>

#include <base-types.hpp>
#include <container/static-array.hpp>
#include <string/format-to.hpp>
#include <utility/as-const.hpp>

namespace NOS {

namespace {

class LocalData
{
public:
    static constexpr size_t BufferSize = 8192;
    static constexpr size_t BufferCount = 16;
    static constexpr size_t LastBuffer = BufferSize - 1;

    Span<char> nextBuffer()
    {
        const size_t offset = _nextBufferIndex * BufferCount;
        _nextBufferIndex = _nextBufferIndex == LastBuffer ? 0 : _nextBufferIndex + 1;
        return {&_buffer[offset], BufferSize};
    }

private:
    StaticArray<char, BufferSize * BufferCount> _buffer;
    size_t _nextBufferIndex{0};
};

struct Out
{
    void write(char c)
    {
        buffer[size++] = c;
    }

    Span<char> buffer;
    size_t size{0};
};

// TODO thread_local
LocalData data;

} // namespace

StringView vformat(StringView fmt, Span<FormatArgument> arguments)
{
    Out out{.buffer = data.nextBuffer()};
    formatTo(out, fmt, arguments);
    return StringView{asConst(out).buffer.data(), out.size};
}

} // namespace NOS
