src = files(
)

libncxx = static_library(
    'ncxx', src,
    install : false,
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
        'tests/type_traits/is_same_tests.cpp',
        'tests/string_view_tests.cpp'
    )

    libncxx_tests = executable(
        'ncxx_tests', [tests], 
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
