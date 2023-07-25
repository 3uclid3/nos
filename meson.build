project('nos', ['c', 'cpp'],
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

project_name = 'nos'

c = meson.get_compiler('c')
cxx = meson.get_compiler('cpp')
ld = cxx.get_linker_id()
arch = host_machine.cpu_family()
buildtype = get_option('buildtype')

config_dir = meson.source_root() / 'config'
log_dir = meson.source_root() / 'log'
sysroot_dir = meson.source_root() / 'sysroot'

# arch
supported_archs = [
#    'aarch64',
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
    error('Unknown buildtype ' + arch)
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
    language: ['c', 'cpp']
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
# GCC Warnings

if c.get_id() == 'gcc'
    add_project_arguments(
        [
            '-Wmisleading-indentation', # warn if indentation implies blocks where blocks do not exist
        ],
        language: ['c', 'cpp']
    )
endif

if cxx.get_id() == 'gcc'
    add_project_arguments(
        [
            '-Wduplicated-cond', # warn if if / else chain has duplicated conditions
            '-Wduplicated-branches', # warn if if / else branches have duplicated code
            '-Wlogical-op', # warn about logical operations being used where bitwise were probably wanted
            '-Wuseless-cast', # warn if you perform a cast to the same type
        ],
        language: ['cpp']
    )
endif


# ----------------------------------------
# Compilation arguments

add_project_arguments(
    [
        '-ffreestanding',
        '-fno-stack-protector',
        '-fno-stack-check',
        '-fno-omit-frame-pointer',
        '-fno-lto'
    ],
    language: ['c', 'cpp']
)

if arch == 'x86_64'
    add_project_arguments(['-DNOS_ARCH_X86_64'], language: ['c', 'cpp'])
endif

if meson.is_cross_build()
    add_project_arguments(
        [
            '-fno-pic'
        ],
        language: ['c', 'cpp']
    )
endif


# ----------------------------------------
# Subprojects

limine = subproject('limine')
limine_dep = dependency('limine', fallback: ['limine', 'limine_dep'])

if not meson.is_cross_build()
    catch2 = subproject('catch2')
    catch2_dep = dependency('catch2', fallback: ['catch2', 'catch2_with_main_dep'], default_options:['tests=false'])
endif

# ----------------------------------------
# libs

libs_c_ccp_args = []
if get_option('libs_ubsan')
    libs_c_ccp_args += '-fsanitize=undefined'
endif

subdir('libs/ncxx')


# ----------------------------------------
# Kernel

subdir('kernel')


# ----------------------------------------
# Image

subdir('image')
