src = files(
    'memory/compare.cpp',
    'memory/copy.cpp',
    'memory/move.cpp',
    'memory/set.cpp'
)

c_ccp_args = [
    '-ffreestanding'
]

libcore = static_library(
    'libcore', 
    src,
    install : false,
    c_args : [
        c_ccp_args,
        '-std=gnu11'
    ],
    cpp_args : [
        c_ccp_args,
    ]
)

libcore_dep  = declare_dependency(
   link_with : libcore,
   sources : src,
   include_directories : ['.']
)
