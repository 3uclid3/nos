src = files(
    'log/log.cpp'
)

log = static_library(
    'log', src,
    install : false,
    include_directories : ['.'],
    dependencies : [ncxx_dep],
    c_args : [libs_c_ccp_args],
    cpp_args : [libs_c_ccp_args],
    link_args: [libs_link_args]
)

log_dep  = declare_dependency(
   link_with : log,
   sources : src,
   include_directories : '.'
)

if not meson.is_cross_build()
    test = files(
        'log/log.test.cpp',

        'log/debug/assert.test-helper.cpp'
    )

    log_test = executable(
        'log.test', [test],
        install : false,
        dependencies : [catch2_dep, ncxx_dep, log_dep],
        c_args : [libs_c_ccp_args],
        cpp_args : [libs_c_ccp_args],
        link_args: [libs_link_args]
    )

    test('log', log_test)
endif
