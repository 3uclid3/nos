package("coal")
    add_urls("https://github.com/3uclid3/coal.git")
    add_versions("latest", "main")

    add_includedirs("include")

    on_install(function (package)
        os.cp("include", package:installdir())
    end)