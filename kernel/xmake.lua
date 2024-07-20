
target("anos.deps")
    set_kind("phony")
    set_toolchains("anos-clang", { public = true })

    add_packages(
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

    add_files("**.cpp")
    
    if is_arch("x86_64") then
        add_cxflags(
            "-mcmodel=kernel",
            { force = true }
        )
        add_ldflags(
            "-T" .. "$(projectdir)/kernel/linker-x86_64.ld",
            { force = true }
        )
    end

    on_run(function (target)
    end)
