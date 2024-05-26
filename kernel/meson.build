src = files(
    'kernel/boot/kmain.cpp',
    'kernel/boot/start.cpp',
    'kernel/cxx/cxx-abi.cpp',
    'kernel/log.cpp'
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

subdir('kernel/arch' / arch)

kernel_elf = executable(
    'kernel.elf', src,
    dependencies : [deps],
    include_directories : ['.'],
    c_args : [c_args, args],
    cpp_args : [cxx_args, args],
    link_args : ld_args,
    install : false
)