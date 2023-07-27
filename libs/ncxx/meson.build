src = files(
    'ncxx/string/format.cpp'
)

ncxx = static_library(
    'ncxx', src,
    install : false,
    include_directories : ['.'],
    c_args : [libs_c_ccp_args],
    cpp_args : [libs_c_ccp_args],
)

ncxx_dep  = declare_dependency(
   link_with : ncxx,
   sources : src,
   include_directories : '.'
)

if not meson.is_cross_build()
    test = files(
        'ncxx/algorithm/all.test.cpp',
        'ncxx/algorithm/all-of.test.cpp',
        'ncxx/algorithm/any.test.cpp',
        'ncxx/algorithm/any-of.test.cpp',
        'ncxx/algorithm/find.test.cpp',
        'ncxx/algorithm/find-if.test.cpp',
        'ncxx/algorithm/none.test.cpp',
        'ncxx/algorithm/none-of.test.cpp',
        'ncxx/container/array.test.cpp',
        'ncxx/debug/assert.test-helper.cpp',
        'ncxx/functional/reference-wrapper.test.cpp',
        'ncxx/hash/crc32.test.cpp',
        'ncxx/memory/allocator/null-allocator.test.cpp',
        'ncxx/memory/allocator/stack-allocator.test.cpp',
        'ncxx/memory/tagged-ptr.test.cpp',
        'ncxx/range/all.test.cpp',
        'ncxx/range/all-of.test.cpp',
        'ncxx/range/any.test.cpp',
        'ncxx/range/any-of.test.cpp',
        'ncxx/range/find.test.cpp',
        'ncxx/range/find-if.test.cpp',
        'ncxx/range/none.test.cpp',
        'ncxx/range/none-of.test.cpp',
        'ncxx/string/format-to.test.cpp',
        'ncxx/string/string-view.test.cpp',
        'ncxx/string/to-string-view.test.cpp',
        'ncxx/type-list/concatenate-transform-type-list.test.cpp',
        'ncxx/type-list/concatenate-type-lists.test.cpp',
        'ncxx/type-list/convert-type-list.test.cpp',
        'ncxx/type-list/enable-if-found-in-type-list.test.cpp',
        'ncxx/type-list/enable-if-found-in-types.test.cpp',
        'ncxx/type-list/filter-type-list.test.cpp',
        'ncxx/type-list/filter-types.test.cpp',
        'ncxx/type-list/for-each-type-list.test.cpp',
        'ncxx/type-list/for-each-types.test.cpp',
        'ncxx/type-list/index-of-from-type-list.test.cpp',
        'ncxx/type-list/index-of-from-types.test.cpp',
        'ncxx/type-list/remove-range-from-type-list.test.cpp',
        'ncxx/type-list/remove-range-from-types.test.cpp',
        'ncxx/type-list/transform-type-list.test.cpp',
        'ncxx/type-list/type-at-from-type-list.test.cpp',
        'ncxx/type-list/type-at-from-types.test.cpp',
        'ncxx/type-list/type-for-bytes-from-type-list.test.cpp',
        'ncxx/type-list/type-for-bytes-from-types.test.cpp',
        'ncxx/type-list/type-list-contains.test.cpp',
        'ncxx/type-list/type-list-from-parameters.test.cpp',
        'ncxx/type-list/type-list-size.test.cpp',
        'ncxx/type-list/types-contains.test.cpp',
        'ncxx/type-list/types-size.test.cpp',
        'ncxx/type-trait/is-array.test.cpp',
        'ncxx/type-trait/is-same.test.cpp',
        'ncxx/type-trait/is-static-array.test.cpp',
        'ncxx/type-trait/is-enum-class.test.cpp',
        'ncxx/type-trait/type-for-bits.test.cpp',
        'ncxx/type-trait/type-enum-value-name.test.cpp',
        'ncxx/type-trait/type-full-name.test.cpp',
        'ncxx/type-trait/type-name.test.cpp',
        'ncxx/utility/enum-string.test.cpp',
        'ncxx/utility/on-scope-exit.test.cpp',
        'ncxx/basic-types.test.cpp'
    )

    ncxx_test = executable(
        'ncxx.test', [test],
        install : false,
        dependencies : [catch2_dep, ncxx_dep]
    )

    test('ncxx', ncxx_test)
endif
