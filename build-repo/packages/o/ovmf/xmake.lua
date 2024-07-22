package("ovmf")
    add_urls("https://github.com/3uclid3/ovmf-binaries.git")
    add_versions("latest", "main")

    on_install(function (package)
        if is_arch("x86_64") then
            os.cp("OVMF_X64.fd", package:installdir("ovmf-binaries"))
        elseif is_arch("aarch64") then
            os.cp("OVMF_AA64.fd", package:installdir("ovmf-binaries"))
        else
            raise("unknown ovmf architecture")
        end
    end)
