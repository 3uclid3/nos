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

using TestArray = ArrayObject<Fake::Object, Memory::StackAllocator<StackBufferSize, alignOf<Fake::Object>()>, size_t>;

TEST_CASE("removeAt", "[Array], [ArrayObject]")
{
    TestArray array{10};
    REQUIRE(array.size() == 10);
    for (size_t i = 0; i < array.size(); ++i) array[i].value = static_cast<int>(i);

    array.removeAt(5);
    CHECK(array.size() == 9);
    CHECK(array[5].value == 6);

    array.removeAt(2);
    CHECK(array.size() == 8);
    CHECK(array[2].value == 3);

    array.removeAt(2);
    CHECK(array.size() == 7);
    CHECK(array[2].value == 4);
}

TEST_CASE("removeAtSwapLast", "[Array], [ArrayObject]")
{
    TestArray array{10};
    REQUIRE(array.size() == 10);
    for (size_t i = 0; i < array.size(); ++i) array[i].value = static_cast<int>(i);

    Fake::Object::dtorCount = 0;

    array.removeAtSwapLast(5);
    CHECK(Fake::Object::dtorCount == 2);
    CHECK(array.size() == 9);
    CHECK(array[5].value == 9);

    array.removeAtSwapLast(2);
    CHECK(Fake::Object::dtorCount == 4);
    CHECK(array.size() == 8);
    CHECK(array[2].value == 8);

    array.removeAtSwapLast(2);
    CHECK(Fake::Object::dtorCount == 6);
    CHECK(array.size() == 7);
    CHECK(array[2].value == 7);
}

TEST_CASE("removeOne", "[Array], [ArrayObject]")
{
    TestArray array{10};
    REQUIRE(array.size() == 10);
    for (size_t i = 0; i < array.size(); ++i) array[i].value = static_cast<int>(i);

    array.removeOne(Fake::Object{5});
    CHECK(array.size() == 9);
    CHECK(array[5].value == 6);

    array.removeOne(Fake::Object{2});
    CHECK(array.size() == 8);
    CHECK(array[2].value == 3);

    array.removeOne(Fake::Object{2});
    CHECK(array.size() == 8);
    CHECK(array[2].value == 3);
}

TEST_CASE("removeOneSwapLast", "[Array], [ArrayObject]")
{
    TestArray array{10};
    REQUIRE(array.size() == 10);
    for (size_t i = 0; i < array.size(); ++i) array[i].value = static_cast<int>(i);

    Fake::Object::dtorCount = 0;

    // 3 dtor for tmp in swap

    array.removeOneSwapLast(Fake::Object(5));
    CHECK(Fake::Object::dtorCount == 3);
    CHECK(array.size() == 9);
    CHECK(array[5].value == 9);

    array.removeOneSwapLast(Fake::Object(2));
    CHECK(Fake::Object::dtorCount == 6);
    CHECK(array.size() == 8);
    CHECK(array[2].value == 8);

    array.removeOneSwapLast(Fake::Object(3));
    CHECK(Fake::Object::dtorCount == 9);
    CHECK(array.size() == 7);
    CHECK(array[3].value == 7);

    array.removeOneSwapLast(Fake::Object(3));
    CHECK(Fake::Object::dtorCount == 10);
    CHECK(array.size() == 7);
}

TEST_CASE("removeFirstSwapLast", "[Array], [ArrayObject]")
{
    TestArray array{10};
    REQUIRE(array.size() == 10);
    for (size_t i = 0; i < array.size(); ++i) array[i].value = static_cast<int>(i);

    Fake::Object::dtorCount = 0;

    // 2 dtor for tmp in swap

    array.removeFirstSwapLast();
    CHECK(Fake::Object::dtorCount == 2);
    CHECK(array.size() == 9);
    CHECK(array.first().value == 9);

    array.removeFirstSwapLast();
    CHECK(Fake::Object::dtorCount == 4);
    CHECK(array.size() == 8);
    CHECK(array.first().value == 8);

    array.removeFirstSwapLast();
    CHECK(Fake::Object::dtorCount == 6);
    CHECK(array.size() == 7);
    CHECK(array.first().value == 7);
}

TEST_CASE("removeLast", "[Array], [ArrayObject]")
{
    TestArray array{10};

    Fake::Object::dtorCount = 0;

    array.removeLast();
    CHECK(Fake::Object::dtorCount == 1);
    CHECK(array.size() == 9);

    array.removeLast();
    CHECK(Fake::Object::dtorCount == 2);
    CHECK(array.size() == 8);

    array.removeLast();
    CHECK(Fake::Object::dtorCount == 3);
    CHECK(array.size() == 7);
}

} // namespace NOS::Details
