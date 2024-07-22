
target("anos.deps")
    set_kind("phony")
    set_toolchains("anos-clang", { public = true })

    add_packages(
        "libstdcxx-fh",
        "limine",
        { public = true }
    )

    if is_arch("x86_64") then
        add_cxflags(
            "-mno-mmx",
            "-mno-sse",
            "-mno-sse2",
            { force = true, public = true }
        )
    end

target("anos.elf")
    set_default(false)
    set_kind("binary")
     
    add_deps("anos.deps")

    -- files
    add_files("**.cpp")

    if is_arch("x86_64") then
       -- add_files("arch/x86_64/**.cpp")
       -- add_files("arch/x86_64/**.S")
    elseif is_arch("aarch64") then
        -- add_files("arch/aarch64/**.cpp")
        -- add_files("arch/aarch64/**.S")
    end
    
    -- flags just for kernel
    add_ldflags(
        "-zmax-page-size=0x1000",
        { force = true }
    )

    if is_arch("x86_64") then
        add_cxflags(
            "-mcmodel=kernel",
            { force = true }
        )
        add_ldflags(
            "-T" .. "$(projectdir)/kernel/linker-x86_64.ld",
            { force = true }
        )
    elseif is_arch("aarch64") then
        add_ldflags(
            "-T" .. "$(projectdir)/kernel/linker-aarch64.ld",
            { force = true }
        )
    end

    on_run(function (target)
    end)
