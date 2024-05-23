limine_dir = meson.source_root() / 'subprojects/limine'

iso_dir = '/tmp' / meson.project_name() / 'iso'
iso_files = [
    limine.get_variable('binaries'),
    config_dir / 'limine.cfg'
]

isoiso = custom_target('iso',
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