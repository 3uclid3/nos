src = files(
    'kernel/boot/limine.cpp',
    'kernel/boot/start.cpp',
    'kernel/cxx/cxa.cpp',
    'kernel/debug/assert.cpp',
    'kernel/libc/string.cpp',
    'kernel/log/logger.cpp',
    'kernel/memory/allocate.cpp',
    'kernel/memory/physical_memory.cpp',
    'kernel/kernel.cpp'
)

c_args = get_option('kernel_cflags').split()
cxx_args = get_option('kernel_cxxflags').split()

ld_args = [
    '-Wl,-T,' + meson.current_source_dir() / 'linker' / arch + '.ld',
    '-Wl,-z,max-page-size=0x1000',
    '-nostdlib',
    '-static'
]

args = [ ]
if get_option('kernel_ubsan')
#    cxx_args += '-fsanitize=undefined'
endif

configure_file(
    input: 'config_files/arch.hpp.in',
    output: 'kernel_arch.hpp',
    configuration: {
        'ARCH': arch
    }
)

configure_file(
    input: 'config_files/config.hpp.in',
    output: 'kernel_config.hpp',
    configuration: {
        'LOGGER_STACK_ALLOCATOR_SIZE': 64
    }
)

subdir('kernel/arch' / arch)

kernel_elf = executable(
    'kernel.elf', src,
    dependencies : [deps],
    include_directories : [
        './kernel/libc',
    ],
    c_args : [c_args, args],
    cpp_args : [cxx_args, args],
    link_args : ld_args,
    install : false
)