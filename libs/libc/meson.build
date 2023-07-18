src = files(
    'source/string/memcmp.c',
    'source/string/memcpy.c',
    'source/string/memmove.c',
    'source/string/memset.c'
)

libc = static_library(
    'c', src,
    install : false,
    include_directories : ['source', 'include'],
    c_args : [
        '-ffreestanding',
        '-std=gnu11'
    ],
)

libc_dep  = declare_dependency(
   link_with : libc,
   sources : src,
   include_directories : 'include'
)

if not meson.is_cross_build()
    tests = files(
        'tests/string/memcmp_tests.cpp',
        'tests/string/memcpy_tests.cpp',
        'tests/string/memmove_tests.cpp',
        'tests/string/memset_tests.cpp'
    )

    libc_tests = executable(
        'c_tests', [src, tests], 
        install : false,
        dependencies : catch2_dep,
        include_directories : [
            'include_with_prefix',
            'source',
            'tests'
        ],
        c_args: '-DNOS_LIBC_API_USE_PREFIX'
    )

    test('libc', libc_tests)
endif