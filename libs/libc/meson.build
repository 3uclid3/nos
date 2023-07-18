src = files(
    'string/memcmp.c',
    'string/memcpy.c',
    'string/memmove.c',
    'string/memset.c'
)

inc_dirs = ['include']

libc = static_library(
    'c', 
    src,
    install : false,
    include_directories : inc_dirs,
    c_args : [
        '-ffreestanding',
        '-std=gnu11'
    ],
)

libc_dep  = declare_dependency(
   link_with : libc,
   sources : src,
   include_directories : inc_dirs
)
