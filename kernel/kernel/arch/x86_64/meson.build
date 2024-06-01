src += files(
    'cpu/cpu.cpp',
    'cpu/gdt.cpp',
    'cpu/idt.cpp',
    'cpu/idt.S',
    'cpu/pic.cpp',
    'drivers/com_port_logger.cpp',
    'drivers/com_port.cpp',
    'drivers/serial_port.cpp',
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
