src_files = files(
    './kernel.cpp'
)

linker_file_path = meson.current_source_dir() / 'arch' / arch / 'linker.ld'

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
    'kernel.elf', src_files,
    install : false,
    pie: true,
    dependencies : [
        dependency('limine'),
        libcore_dep
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