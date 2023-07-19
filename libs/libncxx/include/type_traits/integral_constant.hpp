namespace nos {

template<typename T, T Value>
struct integral_constant
{
    using value_type = T;

    static constexpr value_type value = Value;

    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

struct false_type : public integral_constant<bool, false>
{};

struct true_type : public integral_constant<bool, true>
{};

} // namespace nos
