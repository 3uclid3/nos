limine_dir = meson.source_root() / 'subprojects/limine'

image_dir = '/tmp' / project_name / 'image'
image_files = [
    limine.get_variable('binaries'),
    config_dir / 'limine.cfg'
]

image = custom_target('image',
    input : [kernel],
    output : project_name + '-' + arch + '.iso',
    build_by_default : true, console : true, install : false,
    depends : [kernel],
    command : [
        'rm', '-rf', image_dir, '&&',
        'mkdir', '-p', image_dir, '&&',
        'mkdir', '-p', image_dir / 'EFI/BOOT', '&&',
        'cp', '@INPUT0@', image_dir / kernel.name(), '&&',
        'cp', image_files, image_dir, '&&',
        'cp', limine_dir / 'BOOTAA64.EFI', image_dir / 'EFI/BOOT/BOOTAA64.EFI', '&&',
        'cp', limine_dir / 'BOOTIA32.EFI', image_dir / 'EFI/BOOT/BOOTIA32.EFI', '&&',
        'cp', limine_dir / 'BOOTRISCV64.EFI', image_dir / 'EFI/BOOT/BOOTRISCV64.EFI', '&&',
        'cp', limine_dir / 'BOOTX64.EFI', image_dir / 'EFI/BOOT/BOOTX64.EFI', '&&',
        'xorriso', '-as', 'mkisofs', 
        '-b', 'limine-bios-cd.bin',
        '-no-emul-boot', 
        '-boot-load-size', '4',
        '-boot-info-table',
        '--efi-boot', 'limine-uefi-cd.bin', 
        '-efi-boot-part',
        '--efi-boot-image', 
        '--protective-msdos-label',
        image_dir, 
        '-o', '@OUTPUT@', '&&',
        'rm', '-rf', image_dir
    ]
)
