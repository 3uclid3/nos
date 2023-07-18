src = files(
)

libcxx = static_library(
    'cxx', src,
    install : false,
    include_directories : ['source', 'include'],
    c_args : [
        '-ffreestanding',
        '-std=gnu11'
    ],
)

libcxx_dep  = declare_dependency(
   link_with : libcxx,
   sources : src,
   include_directories : 'include'
)

if not meson.is_cross_build()
    tests = files(
        'tests/type_traits/is_same_tests.cpp',
        'tests/string_view_tests.cpp'
    )

    libcxx_tests = executable(
        'cxx_tests', [tests], 
        install : false,
        dependencies : [catch2_dep, libcxx_dep],
        include_directories : [
            'include',
            'source',
            'tests'
        ]
    )

    test('libcxx', libcxx_tests)
endif