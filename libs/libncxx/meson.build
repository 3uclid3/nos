src = files(
#    'source/debug/assert.cpp'
)

libncxx = static_library(
    'libncxx', src,
    install : false,
    name_prefix: '',
    include_directories : ['source', 'include'],
    c_args : [
        '-ffreestanding',
        '-std=gnu11'
    ],
)

libncxx_dep  = declare_dependency(
   link_with : libncxx,
   sources : src,
   include_directories : 'include'
)

if not meson.is_cross_build()
    tests = files(
        'tests/debug/assert.cpp',
        'tests/container/array-tests.cpp',
        'tests/memory/allocator/null-allocator-tests.cpp',
        'tests/memory/allocator/stack-allocator-tests.cpp',
        'tests/type-traits/is-same-tests.cpp',
        'tests/string/format-to-tests.cpp',
        'tests/string/string-view-tests.cpp',
        'tests/string/to-string-view-tests.cpp'
    )

    libncxx_tests = executable(
        'libncxx_tests', [tests], 
        install : false,
        dependencies : [catch2_dep, libncxx_dep],
        include_directories : [
            'include',
            'source',
            'tests'
        ]
    )

    test('libncxx', libncxx_tests)
endif
