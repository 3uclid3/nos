#include <arch.hpp>
#include <cxx/ubsan.hpp>
#include <kdef.hpp>
#include <klog.hpp>

namespace nos::ubsan {

void print(const char* message, source_location loc)
{
    log::warn("nos: ubsan with message {} at file {}, line {}, column {}", message, loc.file, loc.line, loc.column);
    arch::hcf();
}

} // namespace nos::ubsan

HEDLEY_BEGIN_C_DECLS

void __ubsan_handle_add_overflow(nos::ubsan::overflow_data* data)
{
    nos::ubsan::print("addition overflow", data->location);
}

void __ubsan_handle_sub_overflow(nos::ubsan::overflow_data* data)
{
    nos::ubsan::print("subtraction overflow", data->location);
}

void __ubsan_handle_mul_overflow(nos::ubsan::overflow_data* data)
{
    nos::ubsan::print("multiplication overflow", data->location);
}

void __ubsan_handle_divrem_overflow(nos::ubsan::overflow_data* data)
{
    nos::ubsan::print("division overflow", data->location);
}

void __ubsan_handle_negate_overflow(nos::ubsan::overflow_data* data)
{
    nos::ubsan::print("negation overflow", data->location);
}

void __ubsan_handle_pointer_overflow(nos::ubsan::overflow_data* data)
{
    nos::ubsan::print("pointer overflow", data->location);
}

void __ubsan_handle_shift_out_of_bounds(nos::ubsan::shift_out_of_bounds_data* data)
{
    nos::ubsan::print("shift out of bounds", data->location);
}

void __ubsan_handle_load_invalid_value(nos::ubsan::invalid_value_data* data)
{
    nos::ubsan::print("invalid load value", data->location);
}

void __ubsan_handle_out_of_bounds(nos::ubsan::array_out_of_bounds_data* data)
{
    nos::ubsan::print("array out of bounds", data->location);
}

void __ubsan_handle_type_mismatch_v1(nos::ubsan::type_mismatch_v1_data* data, std::uintptr_t ptr)
{
    if (ptr == 0)
        nos::ubsan::print("use of nullptr", data->location);
    else if (ptr & ((1 << data->log_alignment) - 1))
        nos::ubsan::print("unaligned access", data->location);
    else
        nos::ubsan::print("no space for object", data->location);
}

void __ubsan_handle_function_type_mismatch(nos::ubsan::function_type_mismatch_v1_data* data, std::uintptr_t ptr)
{
    nos::ubsan::print("call to a function through pointer to incorrect function", data->location);
}

void __ubsan_handle_function_type_mismatch_v1(nos::ubsan::function_type_mismatch_v1_data* data, std::uintptr_t ptr, std::uintptr_t calleeRTTI, std::uintptr_t fnRTTI)
{
    nos::ubsan::print("call to a function through pointer to incorrect function", data->location);
}

void __ubsan_handle_vla_bound_not_positive(nos::ubsan::negative_vla_data* data)
{
    nos::ubsan::print("variable-length argument is negative", data->location);
}

void __ubsan_handle_nonnull_return(nos::ubsan::nonnull_return_data* data)
{
    nos::ubsan::print("non-null return is null", data->location);
}

void __ubsan_handle_nonnull_return_v1(nos::ubsan::nonnull_return_data* data)
{
    nos::ubsan::print("non-null return is null", data->location);
}

void __ubsan_handle_nonnull_arg(nos::ubsan::nonnull_arg_data* data)
{
    nos::ubsan::print("non-null argument is null", data->location);
}

void __ubsan_handle_builtin_unreachable(nos::ubsan::unreachable_data* data)
{
    nos::ubsan::print("unreachable code reached", data->location);
}

void __ubsan_handle_invalid_builtin(nos::ubsan::invalid_builtin_data* data)
{
    nos::ubsan::print("invalid builtin", data->location);
}

void __ubsan_handle_float_cast_overflow(nos::ubsan::float_cast_overflow_data* data)
{
    nos::ubsan::print("float cast overflow", data->location);
}

void __ubsan_handle_missing_return(nos::ubsan::missing_return_data* data)
{
    nos::ubsan::print("missing return", data->location);
}

void __ubsan_handle_alignment_assumption(nos::ubsan::alignment_assumption_data* data)
{
    nos::ubsan::print("alignment assumption", data->location);
}

HEDLEY_END_C_DECLS
