#pragma once

namespace NOS::Fake {

template<typename TConcrete>
struct BaseObject
{
    bool ctorDefault : 1 {false};
    bool ctorCopy : 1 {false};
    bool ctorMove : 1 {false};
    bool otorCopy : 1 {false};
    bool otorMove : 1 {false};

    inline static void resetCounts()
    {
        ctorCount = 0;
        dtorCount = 0;
        moveCount = 0;
        copyCount = 0;
    }

    inline static int ctorCount = 0;
    inline static int dtorCount = 0;
    inline static int moveCount = 0;
    inline static int copyCount = 0;
};

struct Object : BaseObject<Object>
{
    Object()
    {
        ctorDefault = true;

        ++ctorCount;
    }

    explicit Object(int initialValue)
        : value(initialValue)
        , ctorInt(true)
    {
        ++ctorCount;
    }

    Object(const Object& other)
        : value(other.value)
    {
        ctorCopy = true;
        ++ctorCount;
        ++copyCount;
    }

    Object(Object&& other)
        : value(other.value)
    {
        ctorMove = true;
        ++ctorCount;
        ++moveCount;
    }

    ~Object()
    {
        ++dtorCount;
    }

    Object& operator=(const Object& other)
    {
        value = other.value;
        otorCopy = true;
        ++copyCount;
        return *this;
    }

    Object& operator=(Object&& other)
    {
        value = other.value;
        otorMove = true;
        ++moveCount;
        return *this;
    }

    bool operator==(const Object& other) const
    {
        return value == other.value;
    }

    int value{-1};
    bool ctorInt : 1 {false};
};

struct CopyOnlyObject : BaseObject<CopyOnlyObject>
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

struct MoveOnlyObject : BaseObject<CopyOnlyObject>
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

struct ObjectFixture
{
    ObjectFixture()
    {
        Object::resetCounts();
        CopyOnlyObject::resetCounts();
        MoveOnlyObject::resetCounts();
    }

    virtual ~ObjectFixture()
    {
        Object::resetCounts();
        CopyOnlyObject::resetCounts();
        MoveOnlyObject::resetCounts();
    }
};

} // namespace NOS::Fake