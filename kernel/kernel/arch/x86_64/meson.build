src += files(
    'cpu/cpu.cpp',
    'cpu/gdt.cpp',
    'cpu/idt.cpp',
    'cpu/idt.S',
    'drivers/com-port.cpp',
    'drivers/serial-port.cpp',
    'utility/com-log-printer.cpp',
    'arch.cpp'
)

args += [
    '-march=x86-64',
    '-msoft-float',
    '-mno-mmx',
    '-mno-sse',
    '-mno-sse2',
    '-mno-red-zone',
    '-mcmodel=kernel'
]

ld_args += ['-Wl,-z,noexecstack']
