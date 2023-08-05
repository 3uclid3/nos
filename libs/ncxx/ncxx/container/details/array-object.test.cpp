#include <ncxx/container/details/array-object.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/basic-types.hpp>
#include <ncxx/memory/allocator/stack-allocator.hpp>
#include <ncxx/test/object.fake.hpp>
#include <ncxx/utility/as-const.hpp>

namespace NOS::Details {

static constexpr size_t StackBufferSize = 8192;

template<typename TObject, typename TAction, typename TPostActionCheck>
void checkPrepend(TAction action, TPostActionCheck postActionCheck)
{
    using TestArray = ArrayObject<TObject, Memory::StackAllocator<StackBufferSize, alignOf<TObject>()>, size_t>;
    TestArray array;
    for (int i = 0; i < 150; ++i)
    {
        TObject obj(i);
        action(array, move(obj));

        REQUIRE(array.size() == static_cast<size_t>(i + 1));
        postActionCheck(array);

        for (int j = 0; j <= i; ++j)
        {
            CHECK(array[static_cast<size_t>(j)].value == i - j);
        }
    }
}

template<typename TObject, typename TAction, typename TPostActionCheck>
void checkAppend(TAction action, TPostActionCheck postActionCheck)
{
    using TestArray = ArrayObject<TObject, Memory::StackAllocator<StackBufferSize, alignOf<TObject>()>, size_t>;
    TestArray array;

    for (int i = 0; i < 150; ++i)
    {
        TObject obj(i);
        action(array, move(obj));

        REQUIRE(array.size() == static_cast<size_t>(i + 1));
        postActionCheck(array, static_cast<size_t>(i));

        for (int j = 0; j <= i; ++j)
        {
            CHECK(array[static_cast<size_t>(j)].value == j);
        }
    }
}

template<typename TObject>
void checkEmplaceFirst()
{
    using TestArray = ArrayObject<TObject, Memory::StackAllocator<StackBufferSize, alignOf<TObject>()>, size_t>;
    TestArray array;
    for (int i = 0; i < 150; ++i)
    {
        array.emplaceFirst(i);

        REQUIRE(array.size() == static_cast<size_t>(i + 1));
        CHECK(array[0].ctorInt);

        for (int j = 0; j <= i; ++j)
        {
            CHECK(array[static_cast<size_t>(j)].value == i - j);
        }
    }
}

template<typename TObject>
void checkEmplaceLast()
{
    using TestArray = ArrayObject<TObject, Memory::StackAllocator<StackBufferSize, alignOf<TObject>()>, size_t>;
    TestArray array;

    for (int i = 0; i < 150; ++i)
    {
        array.emplaceLast(i);

        REQUIRE(array.size() == static_cast<size_t>(i + 1));
        CHECK(array[static_cast<size_t>(i)].ctorInt);

        for (int j = 0; j <= i; ++j)
        {
            CHECK(array[static_cast<size_t>(j)].value == j);
        }
    }
}

TEST_CASE("prepend copy", "[Array], [ArrayObject]")
{
    checkPrepend<Fake::Object>([](auto& array, auto&& obj) { array.prepend(asConst(obj)); },
                               [](auto& array) { CHECK(array[0].ctorCopy); });

    checkPrepend<Fake::CopyOnlyObject>([](auto& array, auto&& obj) { array.prepend(obj); },
                                       [](auto& array) { CHECK(array[0].ctorCopy); });
}

TEST_CASE("prepend move", "[Array], [ArrayObject]")
{
    checkPrepend<Fake::Object>([](auto& array, auto&& obj) { array.prepend(move(obj)); },
                               [](auto& array) { CHECK(array[0].ctorMove); });

    checkPrepend<Fake::MoveOnlyObject>([](auto& array, auto&& obj) { array.prepend(move(obj)); },
                                       [](auto& array) { CHECK(array[0].ctorMove); });
}

TEST_CASE("append copy", "[Array], [ArrayObject]")
{
    checkAppend<Fake::Object>([](auto& array, auto&& obj) { array.append(asConst(obj)); },
                              [](auto& array, auto i) { CHECK(array[i].ctorCopy); });

    checkAppend<Fake::CopyOnlyObject>([](auto& array, auto&& obj) { array.append(obj); },
                                      [](auto& array, auto i) { CHECK(array[i].ctorCopy); });
}

TEST_CASE("append move", "[Array], [ArrayObject]")
{
    checkAppend<Fake::Object>([](auto& array, auto&& obj) { array.append(move(obj)); },
                              [](auto& array, auto i) { CHECK(array[i].ctorMove); });

    checkAppend<Fake::MoveOnlyObject>([](auto& array, auto&& obj) { array.append(move(obj)); },
                                      [](auto& array, auto i) { CHECK(array[i].ctorMove); });
}

TEST_CASE("emplaceFirst", "[Array], [ArrayObject]")
{
    checkEmplaceFirst<Fake::Object>();
    checkEmplaceFirst<Fake::CopyOnlyObject>();
    checkEmplaceFirst<Fake::MoveOnlyObject>();
}

TEST_CASE("emplaceLast", "[Array], [ArrayObject]")
{
    checkEmplaceLast<Fake::Object>();
    checkEmplaceLast<Fake::CopyOnlyObject>();
    checkEmplaceLast<Fake::MoveOnlyObject>();
}

} // namespace NOS::Details
