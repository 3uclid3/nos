src = files(
    'source/arch' / arch / 'arch.cpp',
    'source/debug/assert.cpp',
    'source/lang/cxxabi.cpp',
    'source/lang/ubsan.cpp',
    'source/utility/cstring.cpp',
    'source/utility/log.cpp',
    'source/utility/panic.cpp',
    'source/kernel.cpp',
    'source/start.cpp',
)

# x86_64 specific files
if arch == 'x86_64'
    src += files(
        'source/arch/x86_64/cpu/cpu.cpp',
#        'source/arch/x86_64/cpu/gdt.cpp',
        'source/arch/x86_64/drivers/serial.cpp'
    )
endif

linker_file_path = meson.current_source_dir() / 'linker' / arch + '.ld'

c_ccp_args = [
    '-m64',
    '-march=x86-64',
    '-mno-80387',
    '-mno-mmx',
    '-mno-sse',
    '-mno-sse2',
    '-mno-red-zone'
]

if get_option('kernel_ubsan')
    c_ccp_args += '-fsanitize=undefined'
endif

kernel = executable(
    'kernel.elf', src,
    install : false, pie : true,
    include_directories : ['include'],
    dependencies : [
        limine_dep,
        libncxx_dep
    ],
    c_args : [
        c_ccp_args
    ],
    cpp_args : [
        c_ccp_args,
        '-MP'
    ],
    link_args : [
        '-nostdlib',
        '-static',
        '-Xlinker', '--no-dynamic-linker',
        '-z', 'text',
        '-z', 'max-page-size=0x1000',
        '-T', linker_file_path
    ]
)