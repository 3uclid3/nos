project('nos', ['c', 'cpp'],
    version : '0.0.1',
    license: 'MIT',
    default_options : [
        'c_std=c17',
        'cpp_std=c++23',

        'cpp_eh=none',
        'cpp_rtti=false',

        'warning_level=2',
        'werror=true'
    ]
)

c = meson.get_compiler('c')
cxx = meson.get_compiler('cpp')
ld = cxx.get_linker_id()
arch = host_machine.cpu_family()

logfile = meson.project_source_root() / 'log.txt'

iso_dir = '/tmp/iso'
iso_files = [
    meson.project_source_root() / 'kernel/limine.cfg'
]

qemu_args = [
    '-cpu', 'max', '-smp', '4', '-m', '512M',
    '-rtc', 'base=localtime', '-serial', 'stdio',
    '-boot', 'order=d,menu=on'
]

# { arch : [ ovmf_name, bios, xorriso_args, qemu_args ] }
supported_archs = {
    'x86_64': [
        'X64',
        true,
        [
            '-b', 'limine-bios-cd.bin',
            '-no-emul-boot',
            '-boot-load-size', '4',
            '-boot-info-table', '--efi-boot', 'limine-uefi-cd.bin',
            '-efi-boot-part', '--efi-boot-image', '--protective-msdos-label'
        ],
        [
            '-M', 'q35'
        ]
    ]
}

if not supported_archs.has_key(arch)
    error('Unknown architecture ' + arch)
endif

ovmf_id = supported_archs[arch][0]
supports_bios = supported_archs[arch][1]
xorriso_args = supported_archs[arch][2]
qemu_args += supported_archs[arch][3]
qemu = 'qemu-system-' + arch

qemu_dbg_args = [
    '-no-reboot', '-no-shutdown',
    '-d', 'int', '-D', logfile,
    '-monitor', 'telnet:127.0.0.1:12345,server,nowait'
]

if arch == 'x86_64'
    qemu_dbg_args += ['-M', 'smm=off']
endif

if get_option('gdb')
    qemu_dbg_args += ['-s', '-S']
endif

qemu_accel_args = []
if not get_option('noaccel')
    qemu_accel_args += ['-M', 'accel=kvm:hvf:whpx:haxm:tcg']
endif

if get_option('vnc')
    qemu_args += ['-vnc', '127.0.0.1:1']
endif

macros = [
    '-DNOS_ARCH=' + arch
]

warnings = [
    '-Wcast-align', # warn for potential performance problem casts
    '-Wconversion', # warn on type conversions that may lose data
    '-Wdouble-promotion', # warn if float is implicit promoted to double
    '-Wimplicit-fallthrough', # warn on statements that fallthrough without an explicit annotation
    '-Wnon-virtual-dtor', # warn the user if a class with virtual functions has a non-virtual destructor. This helps
    '-Wnull-dereference', # warn if a null dereference is detected
    '-Wold-style-cast', # warn for c-style casts
    '-Woverloaded-virtual', # warn if you overload (not override) a virtual function
    '-Wpedantic', # warn if non-standard C++ is used
    '-Wsign-conversion', # warn on sign conversions
    '-Wunused' # warn on anything being unused
]

add_global_arguments([
    warnings, macros,
    '-ffreestanding',
    '-fno-stack-protector',
    '-fno-omit-frame-pointer',
    '-fno-pic',
    '-fno-pie'
    ],
    language: ['c', 'cpp']
)

add_global_arguments([
    '-fsized-deallocation'
], language: ['cpp'])

limine = subproject('limine', default_options : ['arch=' + arch])
nxx = subproject('nxx', default_options : ['tests=false'])
deps = [
    nxx.get_variable('nxx_dep'),
    limine.get_variable('limine_dep')
]

inc_deps = [ ]
foreach dep : deps
    inc_deps += dep.partial_dependency(includes : true)
endforeach

kernel_elf = [ ]
subdir('kernel')

iso_files += limine.get_variable('limine_binaries')
iso = custom_target('iso',
    input : [kernel_elf],
    output : 'image.iso',
    command : [
        'rm', '-rf', iso_dir, '&&',
        'mkdir', '-p', iso_dir, '&&',
        'cp', '@INPUT0@', iso_dir / 'kernel.elf', '&&',
        'cp', iso_files, iso_dir, '&&',
        'xorriso', '-as', 'mkisofs', xorriso_args, iso_dir, '-o', '@OUTPUT@', '&&',
        supports_bios ? [ limine.get_variable('limine_exec'), 'bios-install', '@OUTPUT@', '&&' ] : [],
        'rm', '-rf', iso_dir
    ],
    build_by_default : true,
    console : true,
    install : false,
    depends : [kernel_elf]
)
 
 
if supports_bios
    run_target('qemu_run_with_bios',
        command : [qemu, qemu_args, qemu_accel_args, '-cdrom', iso],
        depends : iso
    )

    run_target('qemu_debug_with_bios',
        command : [qemu, qemu_args, qemu_dbg_args, '-cdrom', iso],
        depends : iso
    )
endif

ovmf_binaries = subproject('ovmf_binaries')
ovmf = ovmf_binaries.get_variable(ovmf_id)

run_target('qemu_run_with_uefi',
    command : [qemu, qemu_args, qemu_accel_args, '-cdrom', iso, '-bios', ovmf],
    depends : iso
)

run_target('qemu_debug_with_uefi',
    command : [qemu, qemu_args, qemu_dbg_args, '-cdrom', iso, '-bios', ovmf],
    depends : iso
)