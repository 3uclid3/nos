src = files(
    'source/arch' / arch / 'arch.cpp',
    'source/boot/loader.cpp',
    'source/boot/start.cpp',
    'source/lang/cxxabi.cpp',
    'source/utility/cstring.cpp',
    'source/utility/log.cpp',
    'source/kernel.cpp'
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
    '-ffreestanding',
    '-fno-stack-protector',
    '-fno-stack-check',
    '-fno-lto',
#        '-fPIC',
    '-m64',
    '-march=x86-64',
#        '-mabi=sysv',
    '-mno-80387',
    '-mno-mmx',
    '-mno-sse',
    '-mno-sse2',
    '-mno-red-zone'
]

kernel_elf = executable(
    'kernel.elf', src,
    install : false, pie : true,
    include_directories : ['include'],
    dependencies : [
        limine_dep,
        libncxx_dep
    ],
    c_args : [
        c_ccp_args,
        '-std=gnu11'
    ],
    cpp_args : [
        c_ccp_args,
        '-MP'
    ],
    link_args : [
#        '-Xlinker', '-m elf_x86_64',
        '-nostdlib',
        '-static',
        '-Xlinker', '-pie',
        '-Xlinker', '--no-dynamic-linker',
        '-z', 'text',
        '-z', 'max-page-size=0x1000',
        '-T', linker_file_path
    ]
)