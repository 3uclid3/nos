#pragma once

#include <ncxx/type-trait/tag-type.hpp>

namespace NOS {

namespace Details {

template<typename... TTypes>
struct ForEachTypesImpl
{
    template<typename TFunctor>
    static constexpr void calls(TFunctor& functor)
    {
        (functor(TagType<TTypes>()), ...);
    }
};

}

} // namespace NOS::Details
