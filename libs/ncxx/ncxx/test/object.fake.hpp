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

    ~Object()
    {
        ++dtorCount;
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

    bool operator==(const Object& other) const
    {
        return value == other.value;
    }

    int value{-1};
    bool ctorInt : 1 {false};
    bool ctorCopy : 1 {false};
    bool ctorMove : 1 {false};
    bool operatorCopy : 1 {false};
    bool operatorMove : 1 {false};

    inline static int dtorCount = 0;
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

    ~CopyOnlyObject()
    {
        ++dtorCount;
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
    bool ctorInt : 1 {false};
    bool ctorCopy : 1 {false};
    bool operatorCopy : 1 {false};

    inline static int dtorCount = 0;
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

    ~MoveOnlyObject()
    {
        ++dtorCount;
    }

    constexpr MoveOnlyObject& operator=(const MoveOnlyObject& other) = delete;

    constexpr MoveOnlyObject& operator=(MoveOnlyObject&& other)
    {
        value = other.value;
        operatorMove = true;
        return *this;
    }

    int value{-1};
    bool ctorInt : 1 {false};
    bool ctorMove : 1 {false};
    bool operatorMove : 1 {false};

    inline static int dtorCount = 0;
};

struct TrivialObject
{
    int value{0};
};

} // namespace NOS::Fake