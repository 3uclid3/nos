#include <kernel/arch/interrupt.hpp>
#include <kernel/utility/log.hpp>
#include <ncxx/basic-types.hpp>
#include <ncxx/preprocessor/unused.hpp>

namespace NOS::UBSan {

struct SourceLocation
{
    const char* fileName;
    u32_t line;
    u32_t column;
};

struct TypeDescriptor
{
    u16_t typeKind;
    u16_t typeInfo;
    char typeName[1];
};

struct TypeMismatchData
{
    SourceLocation location;
    TypeDescriptor* type;
    unsigned long alignment;
    unsigned char typeCheckKind;
};

struct FunctionTypeMismatchData
{
    SourceLocation location;
    TypeDescriptor* type;
    unsigned long alignment;
    unsigned char typeCheckKind;
};

struct OverflowData
{
    SourceLocation location;
    TypeDescriptor* type;
};

struct ShiftOutOfBoundsData
{
    SourceLocation location;
    TypeDescriptor* lhsType;
    TypeDescriptor* rhsType;
};

struct ArrayOutOfBoundsData
{
    SourceLocation location;
    TypeDescriptor* arrayType;
    TypeDescriptor* indexType;
};

struct UnreachableData
{
    SourceLocation location;
};

struct InvalidBuiltinData
{
    SourceLocation location;
    u8_t kind;
};

struct NegativeVlaData
{
    SourceLocation location;
    TypeDescriptor* type;
};

struct InvalidValueData
{
    SourceLocation location;
    TypeDescriptor* type;
};

struct NonNullReturnData
{
    SourceLocation location;
};

struct NonNullArgData
{
    SourceLocation location;
};

struct FloatCastOverflowData
{
    SourceLocation location;
};

struct MissingReturnData
{
    SourceLocation location;
};

struct AlignmentAssumptionData
{
    SourceLocation location;
    SourceLocation assumptionLocation;
    TypeDescriptor* type;
};

static void print(StringView message, SourceLocation location)
{
    Log::warn("Ubsan: {} at file {}, line {}, column {}", message, location.fileName, location.line, location.column);
    Interrupt::hcf();
}

} // namespace NOS::UBSan

extern "C" {

void __ubsan_handle_add_overflow(NOS::UBSan::OverflowData* data)
{
    print("addition overflow", data->location);
}

void __ubsan_handle_sub_overflow(NOS::UBSan::OverflowData* data)
{
    print("subtraction overflow", data->location);
}

void __ubsan_handle_mul_overflow(NOS::UBSan::OverflowData* data)
{
    print("multiplication overflow", data->location);
}

void __ubsan_handle_divrem_overflow(NOS::UBSan::OverflowData* data)
{
    print("division overflow", data->location);
}

void __ubsan_handle_negate_overflow(NOS::UBSan::OverflowData* data)
{
    print("negation overflow", data->location);
}

void __ubsan_handle_pointer_overflow(NOS::UBSan::OverflowData* data)
{
    print("pointer overflow", data->location);
}

void __ubsan_handle_shift_out_of_bounds(NOS::UBSan::ShiftOutOfBoundsData* data)
{
    print("shift out of bounds", data->location);
}

void __ubsan_handle_load_invalid_value(NOS::UBSan::InvalidValueData* data)
{
    print("invalid load value", data->location);
}

void __ubsan_handle_out_of_bounds(NOS::UBSan::ArrayOutOfBoundsData* data)
{
    print("array out of bounds", data->location);
}

void __ubsan_handle_type_mismatch_v1(NOS::UBSan::TypeMismatchData* data, NOS::uintptr_t ptr)
{
    if (ptr == 0)
    {
        print("use of nullptr", data->location);
    }
    else if (ptr & (data->alignment - 1))
    {
        print("unaligned access", data->location);
    }
    else
    {
        print("no space for object", data->location);
    }
}

void __ubsan_handle_function_type_mismatch_v1(NOS::UBSan::FunctionTypeMismatchData* data, NOS::uintptr_t ptr, NOS::uintptr_t calleeRTTI, NOS::uintptr_t fnRTTI)
{
    NOS_UNUSED(ptr);
    NOS_UNUSED(calleeRTTI);
    NOS_UNUSED(fnRTTI);

    print("call to a function through pointer to incorrect function", data->location);
}

void __ubsan_handle_vla_bound_not_positive(NOS::UBSan::NegativeVlaData* data)
{
    print("variable-length argument is negative", data->location);
}

void __ubsan_handle_nonnull_return(NOS::UBSan::NonNullReturnData* data)
{
    print("non-null return is null", data->location);
}

void __ubsan_handle_nonnull_return_v1(NOS::UBSan::NonNullArgData* data)
{
    print("non-null return is null", data->location);
}

void __ubsan_handle_nonnull_arg(NOS::UBSan::NonNullArgData* data)
{
    print("non-null argument is null", data->location);
}

void __ubsan_handle_builtin_unreachable(NOS::UBSan::UnreachableData* data)
{
    print("unreachable code reached", data->location);
}

void __ubsan_handle_invalid_builtin(NOS::UBSan::InvalidBuiltinData* data)
{
    print("invalid builtin", data->location);
}

void __ubsan_handle_float_cast_overflow(NOS::UBSan::FloatCastOverflowData* data)
{
    print("float cast overflow", data->location);
}

void __ubsan_handle_missing_return(NOS::UBSan::MissingReturnData* data)
{
    print("missing return", data->location);
}

void __ubsan_handle_alignment_assumption(NOS::UBSan::AlignmentAssumptionData* data)
{
    print("alignment assumption", data->location);
}
} //
