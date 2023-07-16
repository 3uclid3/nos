#include <type_traits/integral_constant.hpp>

namespace nos
{
    template<typename T0, typename T1>
    struct is_same : false_type
    {
    };

    template<typename T>
    struct is_same<T, T> : true_type
    {
    };

    template<typename T0, typename T1>
    static constexpr auto is_same_v = is_same<T0, T1>::value;
    
} // namespace nos
