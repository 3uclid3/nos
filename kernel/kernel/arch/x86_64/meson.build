src += files(
    'cpu/gdt.cpp',
    'cpu/idt.S',
    'cpu/idt.cpp',
    'cpu/pic.cpp',
    'drivers/com_port_log_sink.cpp',
    'drivers/com_port.cpp',
    'drivers/serial_port.cpp',
    'arch.cpp',
    'cpu.cpp',
)

args += [
    '-march=x86-64',
    '-msoft-float',
    '-mno-mmx',
    '-mno-sse',
    '-mno-sse2',
    '-mno-red-zone',
    '-mcmodel=kernel',
]

ld_args += ['-Wl,-z,noexecstack']