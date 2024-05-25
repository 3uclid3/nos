project('nos', ['cpp'],
    version : '0.0.1',
    license: 'MIT',
    default_options : [
        'c_std=c17',
        'cpp_std=c++20',

        'cpp_eh=none',
        'cpp_rtti=false'
    ]
)

# ----------------------------------------
# Basic vars

cxx = meson.get_compiler('cpp')
ld = cxx.get_linker_id()
arch = host_machine.cpu_family()
buildtype = get_option('buildtype')

config_dir = meson.source_root() / 'config'
log_dir = meson.source_root() / 'log'
sysroot_dir = meson.source_root() / 'sysroot'

# arch
supported_archs = [
    'x86_64'
]

if arch not in supported_archs
    error('Unknown architecture ' + arch)
endif

# buildtype
if buildtype == 'debug'
    buildtype_args = ['-DNOS_DEBUG']
elif buildtype == 'release'
    buildtype_args = ['-DNOS_RELEASE']
else
    error('Unknown buildtype ' + buildtype)
endif

add_project_arguments(buildtype_args, language: ['c', 'cpp'])


# ----------------------------------------
# Warnings

add_project_arguments(
    [
        '-Werror',
        '-Wall',
        '-Wextra',
        '-Wshadow', # warn the user if a variable declaration shadows one from a parent context
        
        # catch hard to track down memory errors
        '-Wcast-align', # warn for potential performance problem casts
        '-Wunused', # warn on anything being unused
        '-Wpedantic', # warn if non-standard C++ is used
        '-Wconversion', # warn on type conversions that may lose data
        '-Wsign-conversion', # warn on sign conversions
        '-Wnull-dereference', # warn if a null dereference is detected
        '-Wdouble-promotion', # warn if float is implicit promoted to double
        '-Wformat=2', # warn on security issues around functions that format output (ie printf)
        '-Wimplicit-fallthrough' # warn on statements that fallthrough without an explicit annotation
    ],
    language: ['cpp']
)

add_project_arguments(
    [
        '-Wextra-semi', # Warn about semicolon after in-class function definition.
        '-Wnon-virtual-dtor', # warn the user if a class with virtual functions has a non-virtual destructor. This helps

        # catch hard to track down memory errors
        '-Wold-style-cast', # warn for c-style casts
        '-Woverloaded-virtual', # warn if you overload (not override) a virtual function
    ],
    language: ['cpp']
)


# ----------------------------------------
# Compilation arguments

add_project_arguments(
    [
        '-ffreestanding',
        '-fno-stack-protector',
        '-fno-stack-check',
        '-fno-omit-frame-pointer',
        '-fno-lto',
        '-fno-pic'
    ],
    language: ['cpp']
)

if arch == 'x86_64'
    add_project_arguments(['-DNOS_ARCH_X86_64'], language: ['cpp'])
endif


# ----------------------------------------
# Subprojects

subproject_root = meson.source_root() / 'subprojects'

limine = subproject('limine')
limine_dep = limine.get_variable('limine_dep')

nxx = subproject('nxx')
nxx_dep = nxx.get_variable('nxx_dep')

# ----------------------------------------
# Kernel

subdir('kernel')


# ----------------------------------------
# ISO

limine_dir = subproject_root / 'limine'

iso_dir = '/tmp' / meson.project_name() / 'iso'
iso_files = [
    limine.get_variable('binaries'),
    config_dir / 'limine.cfg'
]

iso = custom_target('iso',
    input : [kernel],
    output : meson.project_name() + '-' + arch + '.iso',
    build_by_default : true, console : true, install : false,
    depends : [kernel],
    command : [
        'rm', '-rf', iso_dir, '&&',
        'mkdir', '-p', iso_dir, '&&',
        'mkdir', '-p', iso_dir / 'EFI/BOOT', '&&',
        'cp', '@INPUT0@', iso_dir / kernel.name(), '&&',
        'cp', iso_files, iso_dir, '&&',
        'cp', limine_dir / 'BOOTAA64.EFI', iso_dir / 'EFI/BOOT/BOOTAA64.EFI', '&&',
        'cp', limine_dir / 'BOOTIA32.EFI', iso_dir / 'EFI/BOOT/BOOTIA32.EFI', '&&',
        'cp', limine_dir / 'BOOTRISCV64.EFI', iso_dir / 'EFI/BOOT/BOOTRISCV64.EFI', '&&',
        'cp', limine_dir / 'BOOTX64.EFI', iso_dir / 'EFI/BOOT/BOOTX64.EFI', '&&',
        'xorriso', '-as', 'mkisofs', 
        '-b', 'limine-bios-cd.bin',
        '-no-emul-boot', 
        '-boot-load-size', '4',
        '-boot-info-table',
        '--efi-boot', 'limine-uefi-cd.bin', 
        '-efi-boot-part',
        '--efi-boot-image', 
        '--protective-msdos-label',
        iso_dir, 
        '-o', '@OUTPUT@', '&&',
        'rm', '-rf', iso_dir
    ]
)