package("hedley")
    set_kind("library", {headeronly = true})

    add_urls("https://github.com/nemequ/hedley/archive/refs/tags/$(version).tar.gz",
             "https://github.com/nemequ/hedley.git")

    add_versions("v15", "e91c71b58f59d08c7b8289be8f687866863d934dfaa528e4be30b178139ae863")

    on_install(function (package)
        os.cp("hedley.h", package:installdir("include/hedley"))
    end)
