set_project("nos")
set_version("v0.1")

set_license("MIT")

add_rules("plugin.compile_commands.autoupdate", { outputdir = "$(buildir)" })

set_policy("run.autobuild", true)
set_policy("build.c++.modules", true)

set_allowedarchs("x86_64", "aarch64")
set_defaultarchs("x86_64")

set_allowedplats("nos")
set_defaultplat("nos")

set_languages("c17", "c++23")

add_rules("mode.debug", "mode.release")


-- options -->

option("extra_cflags")
    set_default("")
    set_showmenu(true)
    set_description("Extra CFLAGS")

option("extra_cxxflags")
    set_default("")
    set_showmenu(true)
    set_description("Extra CXXFLAGS")

option("extra_qemuflags")
    set_default("")
    set_showmenu(true)
    set_description("Extra QEMU flags")

option("ubsan")
    set_default(false)
    set_showmenu(true)
    set_description("UBSanitizer in kernel and modules. Requires rebuild")

option("vmm_5lvl")
    set_default(false)
    set_showmenu(true)
    set_description("5 level paging. Requires rebuild")

option("syscall_log")
    set_default(false)
    set_showmenu(true)
    set_description("Log system calls to serial. Requires rebuild")

option("qaccel")
    set_default(false)
    set_showmenu(true)
    set_description("Enable QEMU accelerators. Disabled when debugging")

option("qgdb")
    set_default(false)
    set_showmenu(true)
    set_description("Pass '-s -S' to QEMU when debugging")

option("qvnc")
    set_default(false)
    set_showmenu(true)
    set_description("Start headless QEMU VNC server on localhost:5901")

-- <-- options


-- functions -->

local function multi_insert(list, ...)
    for idx, val in ipairs({ ... }) do
        list[#list + 1] = val
    end
end

local function get_targetfile(prefix, ext)
    local ret = path.join(os.tmpdir(), prefix .. "-" .. get_config("arch") .. ext)
    return ret
end

-- <-- functions

-- variables -->

local logfile = os.projectdir() .. "/log.txt"

local qemu_args = {
    "-cpu", "max", "-smp", "4", "-m", "512M",
    "-rtc", "base=localtime", "-serial", "stdio",
    "-boot", "order=d,menu=on,splash-time=100",
    "-no-reboot", "-no-shutdown",
    "-d", "int", "-D", logfile,
}

local qemu_accel_args = {
    "-M", "accel=kvm:hvf:whpx:haxm:tcg"
}

local qemu_dbg_args = {
    "-monitor", "telnet:127.0.0.1:12345,server,nowait"
}

local ovmf_id = ""
local bios = false

-- <-- variables

-- toolchain -->

toolchain("nos-clang")
    set_kind("standalone")

    set_toolset("as", "clang")
    set_toolset("cc", "clang")
    set_toolset("cxx", "clang++", "clang")

    set_toolset("ld", "ld.lld", "lld")

    set_toolset("ar", "llvm-ar", "ar")
    set_toolset("strip", "llvm-strip", "strip")

    add_defines("LVL5_PAGING=" .. (is_config("vmm_5lvl") and "1" or "0"))
    add_defines("SYSCALL_LOG=" .. (is_config("syscall_log") and "1" or "0"))

    add_defines("UACPI_FORMATTED_LOGGING")

    on_check(function (toolchain)
        return import("lib.detect.find_tool")("clang")
    end)

    on_load(function (toolchain)
        local cx_args = {
            "-ffreestanding",
            "-fno-stack-protector",
            "-fno-omit-frame-pointer",
            "-fno-pic",
            "-fno-pie",

            "-nostdinc",
            "-msoft-float",

            -- using set_warnings causes some argument ordering issues
            "-Wall", "-Werror",

            "-Wno-error=#warnings",
            "-Wno-builtin-macro-redefined",
            "-Wno-macro-redefined",
            "-Wno-nan-infinity-disabled",
            "-Wno-frame-address"
        }
        local c_args = { }
        local cxx_args = {
            "-fno-rtti",
            "-fno-exceptions",
            "-fsized-deallocation",

            "-DMAGIC_ENUM_NO_STREAMS=1",
            "-DFMT_STATIC_THOUSANDS_SEPARATOR=1",
            "-DFMT_USE_LONG_DOUBLE=0",
            "-DFMT_USE_DOUBLE=0",
            "-DFMT_USE_FLOAT=0",
            "-DFMT_USE_INT128=0",

            "-Wno-unused-parameter",
            "-Wno-non-virtual-dtor"
        }

        local ld_args = {
            "-nostdlib",
            "-static",
            "-znoexecstack"
        }

        local target = ""

        if is_arch("x86_64") then
            target = "x86_64-pc-elf"

            table.insert(cx_args, "-march=x86-64")
            table.insert(cx_args, "-mno-red-zone")
        elseif is_arch("aarch64") then
            target = "aarch64-elf"

            table.insert(cx_args, "-mcmodel=small")
        end

        table.insert(cx_args, "--target=" .. target)

        table.insert(c_args, get_config("extra_cflags"))
        table.insert(cxx_args, get_config("extra_cxxflags"))

        if is_config("ubsan") then
            set_policy("build.sanitizer.undefined", true)
        end

        toolchain:add("cxflags", cx_args, { force = true })
        toolchain:add("cflags", c_args, { force = true })
        toolchain:add("cxxflags", cxx_args, { force = true })

        toolchain:add("ldflags", ld_args, { force = true })

        toolchain:add("includedirs",
            "$(projectdir)/include",
            "$(projectdir)/include/std",
            "$(projectdir)/include/std/stubs",
            "$(projectdir)/include/libc",
            "$(projectdir)/include/kernel",
            "$(projectdir)/include/modules"
        )
    end)
toolchain_end()

-- <-- toolchain

-- dependencies -->

add_toolchains("nos-clang")

add_repositories("local-repo build-repo")

add_requires(
    "coal",
    "fmt",
    "libstdcxx-fh",
    "limine",
    "magic_enum",
    "ovmf",
    "printf",
    "string"
)

-- <-- dependencies

-- targets.build -->

includes("kernel/xmake.lua")

target("iso")
    set_default(false)
    set_kind("phony")
    
    add_deps("nos.elf")

    add_packages("limine", "ovmf")

    on_clean(function (target)
        os.rm(get_targetfile("image", ".iso"))
    end)

    on_build(function (target)
        import("core.project.project")
        import("core.project.depend")
        import("lib.detect.find_program")

        targetfile = get_targetfile("image", ".iso")
        target:set("values", "targetfile", targetfile)

        local kernel = project.target("nos.elf")

        local iso_dirname = "nos.iso.dir"
        local iso_dir = path.join(os.tmpdir(), iso_dirname)
        local iso_dir_eb = path.join(iso_dir, "EFI/BOOT")

        local limine_binaries = path.join(kernel:pkg("limine"):installdir(), "limine-binaries")
        local limine_exec = path.join(limine_binaries, "limine")

        local iso_files = {
            "$(projectdir)/bootloader/limine.cfg",
            path.join(limine_binaries, "limine-uefi-cd.bin")
        }
        local iso_files_eb = { }

        local xorriso_args = {
            "-as", "mkisofs"
        }

        if is_arch("x86_64") then
            multi_insert(xorriso_args,
                "-b", "limine-bios-cd.bin",
                "-no-emul-boot", "-boot-load-size", "4",
                "-boot-info-table"
            )

            multi_insert(iso_files,
                path.join(limine_binaries, "limine-bios.sys"),
                path.join(limine_binaries, "limine-bios-cd.bin")
            )
            multi_insert(iso_files_eb,
                path.join(limine_binaries, "BOOTX64.EFI"),
                path.join(limine_binaries, "BOOTIA32.EFI")
            )
        elseif is_arch("aarch64") then
            table.insert(iso_files_eb, path.join(limine_binaries, "BOOTAA64.EFI"))
        end

        multi_insert(xorriso_args,
            "--efi-boot", "limine-uefi-cd.bin",
            "-efi-boot-part", "--efi-boot-image",
            "--protective-msdos-label"
        )

        local kernelfile = kernel:targetfile()
        local created = false

        local function create_iso()
            os.tryrm(targetfile)
            os.tryrm(iso_dir)

            os.mkdir(iso_dir)
            os.mkdir(iso_dir_eb)

            print(" => copying target files to temporary iso directory...")

            for idx, val in ipairs(iso_files) do
                os.cp(val, iso_dir)
            end
            for idx, val in ipairs(iso_files_eb) do
                os.cp(val, iso_dir_eb)
            end
            os.cp(kernelfile, path.join(iso_dir, "kernel.elf"))

            multi_insert(xorriso_args,
                iso_dir, "-o", targetfile
            )

            print(" => building the iso...")
            os.execv(find_program("xorriso"), xorriso_args)

            print(" => installing limine...")
            os.execv(limine_exec, { "bios-install", targetfile })

            created = true
            os.tryrm(iso_dir)
        end

        depend.on_changed(create_iso, { files = { kernelfile } })

        if not created and not os.isfile(targetfile) then
            create_iso()
        end
    end)

-- <-- targets.build


-- targets.run -->

task("qemu")
    on_run(function ()
        import("core.base.option")
        import("core.project.project")
        import("lib.detect.find_program")

        local extra_qemu_args = get_config("extra_qemuflags")
        if extra_qemu_args ~= "" then
            table.insert(qemu_args, extra_qemu_args)
        end

        if get_config("qvnc") then
            multi_insert(qemu_args,
                "-vnc", "127.0.0.1:1"
            )
        end

        local qemu_exec = ""
        if is_arch("x86_64") then
            ovmf_id = "X64"
            bios = true

            multi_insert(qemu_args,
                "-M", "q35", "-audiodev", "id=audio,driver=alsa",
                "-machine", "pcspk-audiodev=audio"
            )

            multi_insert(qemu_dbg_args,
                "-M", "smm=off"
            )

            qemu_exec = find_program("qemu-system-x86_64")
        elseif is_arch("aarch64") then
            ovmf_id = "AA64"
            bios = false

            multi_insert(qemu_args,
                "-M", "virt", "-device", "ramfb"
            )

            qemu_exec = find_program("qemu-system-aarch64")
        end

        if not option.get("uefi") and not bios then
            raise("BIOS not supported on this architecture")
        end

        if option.get("debug") then
            multi_insert(qemu_args, unpack(qemu_dbg_args))
            if get_config("qgdb") then
                multi_insert(qemu_args,
                    "-s", "-S"
                )
            end
        elseif get_config("qaccel") then
            multi_insert(qemu_args, unpack(qemu_accel_args))
        end

        local iso = project.target("iso")
        local pkg = iso:pkg("ovmf"):installdir()
        local ovmf_fd = path.join(pkg, "ovmf-binaries/OVMF_" .. ovmf_id .. ".fd")

        multi_insert(qemu_args,
            "-cdrom", iso:get("values", "targetfile")["targetfile"]
        )

        if option.get("uefi") then
            multi_insert(qemu_args,
                "-bios", ovmf_fd
            )
        end

        print(" => running qemu...")
        os.execv(qemu_exec, qemu_args)
    end)

target("bios")
    set_default(false)
    set_kind("phony")
    add_deps("iso")

    on_run(function (target)
        import("core.project.task")
        import("core.project.project")
        task.run("qemu", { uefi = false })
    end)

target("bios-debug")
    set_default(false)
    set_kind("phony")
    add_deps("iso")

    on_run(function (target)
        import("core.project.task")
        import("core.project.project")
        task.run("qemu", { uefi = false, debug = true })
    end)

target("uefi")
    set_default(true)
    set_kind("phony")
    add_deps("iso")

    on_run(function (target)
        import("core.project.task")
        import("core.project.project")
        task.run("qemu", { uefi = true })
    end)

target("uefi-debug")
    set_default(false)
    set_kind("phony")
    add_deps("iso")

    on_run(function (target)
        import("core.project.task")
        import("core.project.project")
        task.run("qemu", { uefi = true, debug = true })
    end)

-- <-- targets.run
