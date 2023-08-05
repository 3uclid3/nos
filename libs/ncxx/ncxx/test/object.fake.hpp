#pragma once

namespace NOS::Fake {

struct Object
{
    constexpr Object() = default;
    constexpr Object(int initialValue)
        : value(initialValue)
    {
        ctorInt = true;
    }

    constexpr Object(const Object& other)
        : value(other.value)
    {
        ctorCopy = true;
    }

    constexpr Object(Object&& other)
        : value(other.value)
    {
        ctorMove = true;
    }

    constexpr Object& operator=(const Object& other)
    {
        value = other.value;
        operatorCopy = true;
        return *this;
    }

    constexpr Object& operator=(Object&& other)
    {
        value = other.value;
        operatorMove = true;
        return *this;
    }

    int value{-1};
    bool ctorInt{false};
    bool ctorCopy{false};
    bool ctorMove{false};
    bool operatorCopy{false};
    bool operatorMove{false};
};

struct CopyOnlyObject
{
    constexpr CopyOnlyObject() = default;
    constexpr CopyOnlyObject(int initialValue)
        : value(initialValue)
    {
        ctorInt = true;
    }

    constexpr CopyOnlyObject(const CopyOnlyObject& other)
        : value(other.value)
    {
        ctorCopy = true;
    }

    constexpr CopyOnlyObject(CopyOnlyObject&& other) = delete;

    constexpr CopyOnlyObject& operator=(const CopyOnlyObject& other)
    {
        value = other.value;
        operatorCopy = true;
        return *this;
    }

    constexpr CopyOnlyObject& operator=(CopyOnlyObject&& other) = delete;

    int value{-1};
    bool ctorInt{false};
    bool ctorCopy{false};
    bool operatorCopy{false};
};

struct MoveOnlyObject
{
    constexpr MoveOnlyObject() = default;
    constexpr MoveOnlyObject(int initialValue)
        : value(initialValue)
    {
        ctorInt = true;
    }

    constexpr MoveOnlyObject(const MoveOnlyObject& other) = delete;

    constexpr MoveOnlyObject(MoveOnlyObject&& other)
        : value(other.value)
    {
        ctorMove = true;
    }

    constexpr MoveOnlyObject& operator=(const MoveOnlyObject& other) = delete;

    constexpr MoveOnlyObject& operator=(MoveOnlyObject&& other)
    {
        value = other.value;
        operatorMove = true;
        return *this;
    }

    int value{-1};
    bool ctorInt{false};
    bool ctorMove{false};
    bool operatorMove{false};
};

} // namespace NOS::Fake