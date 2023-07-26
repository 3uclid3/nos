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
        'ncxx/container/array.test.cpp',
        'ncxx/debug/assert.test-helper.cpp',
        'ncxx/hash/crc32.test.cpp',
        'ncxx/memory/allocator/null-allocator.test.cpp',
        'ncxx/memory/allocator/stack-allocator.test.cpp',
        'ncxx/type-trait/is-same.test.cpp',
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
