#pragma once

namespace NOS {

// clang-format off
struct InputIteratorTag {};
struct OutputIteratorTag {};
struct ForwardIteratorTag : InputIteratorTag {};
struct BidirectionalIteratorTag : ForwardIteratorTag {};
struct RandomAccessIteratorTag : BidirectionalIteratorTag {};
struct ContiguousIteratorTag : RandomAccessIteratorTag {};
// clang-format on

} // namespace NOS
