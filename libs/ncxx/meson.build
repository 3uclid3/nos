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
        'ncxx/debug/assert.test-helper.cpp',
        'ncxx/container/array.test.cpp',
        'ncxx/memory/allocator/null-allocator.test.cpp',
        'ncxx/memory/allocator/stack-allocator.test.cpp',
        'ncxx/type-trait/is-same.test.cpp',
        'ncxx/string/format-to.test.cpp',
        'ncxx/string/string-view.test.cpp',
        'ncxx/string/to-string-view.test.cpp'
    )

    ncxx_test = executable(
        'ncxx.test', [test],
        install : false,
        dependencies : [catch2_dep, ncxx_dep]
    )

    test('ncxx', ncxx_test)
endif
