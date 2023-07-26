#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/type-list-from-parameters.hpp>
#include <ncxx/type-list/type-list.hpp>

namespace NOS {

int freeFunction(f32_t, bool);

struct Functor
{
    int operator()(f32_t, bool);
};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunneeded-internal-declaration"

// capture to prevent lambda from potentially implicitly decay into function pointer
auto lambda = [somethingToCapture = 42](f32_t, bool) -> int {
    return somethingToCapture;
};

#pragma clang diagnostic pop

using ExpectedTypeList = TypeList<f32_t, bool>;

static_assert(IsSameV<ExpectedTypeList, TypeListFromParametersT<decltype(freeFunction)>>);
static_assert(IsSameV<ExpectedTypeList, TypeListFromParametersT<Functor>>);
static_assert(IsSameV<ExpectedTypeList, TypeListFromParametersT<decltype(lambda)>>);

} // namespace NOS
