src = files(
    'kernel/arch/arch.cpp',
    'kernel/debug/assert.cpp',
    'kernel/lang/cxxabi.cpp',
    'kernel/lang/ubsan.cpp',
    'kernel/log/serial-sink.cpp',
    'kernel/memory/allocation.cpp',
    'kernel/utility/cstring.cpp',
    'kernel/utility/panic.cpp',
    'kernel/kernel.cpp',
    'kernel/start.cpp',
)

# x86_64 specific files
if arch == 'x86_64'
    src += files(
        'kernel/arch/x86_64/drivers/serial.cpp',
        'kernel/arch/x86_64/arch.cpp',
        'kernel/arch/x86_64/gdt.cpp',
        'kernel/arch/x86_64/idt.cpp',
        'kernel/arch/x86_64/idt.S',
        'kernel/arch/x86_64/isr.cpp',
        'kernel/arch/x86_64/pic.cpp',
        'kernel/arch/x86_64/tss.cpp'
    )
endif

linker_file_path = meson.current_source_dir() / 'linker' / arch + '.ld'

c_ccp_args = [
    '-m64',
    '-mcmodel=large',
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
    include_directories : ['.'],
    dependencies : [
        limine_dep,
        ncxx_dep,
        log_dep
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
