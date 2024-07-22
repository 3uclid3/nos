# NOS - An OS

An educational project focused on developing a comprehensive operating system from scratch. This project aims to cover various aspects of OS development, including hardware abstraction, memory management, file systems, networking, and more.

## Features

- **Hardware Abstraction and Initialization**: Support for serial communication, GDT, IDT, TSS, PCI, PCIe, MSI, LAPIC, IOAPIC, and more.
- **Memory Management**: Physical and virtual memory management, including support for multiple levels of paging and heap memory.
- **Modules and Drivers**: Implementation of drivers for various hardware components, including network cards and storage devices.
- **File Systems**: Support for multiple file systems such as VFS, TMPFS, PROCFS, EXT2, and FAT32.
- **Networking**: Ethernet, ARP, IPv4, ICMPv4, TCP, and UDP protocols.
- **Userspace and System Calls**: Development of a userspace environment with system call support for multiple architectures.
- **Device Interfaces**: TTY, PTY, character devices, framebuffer devices, and more.
- **Permissions and Security**: File and process permissions, file descriptor management, and other security features.
- **Target Architectures**: Initially aiming for x86_64 with plans to support aarch64 in the future.
- **Symmetric Multiprocessing (SMP)**: Support for SMP to utilize multiple CPU cores effectively.

### TODO List

- **Hardware Abstraction and Initialization**
  - [ ] Serial
  - [ ] GDT
  - [ ] IDT
  - [ ] TSS
  - [ ] PCI
  - [ ] PCIe
  - [ ] MSI
  - [ ] MSI-X
  - [ ] LAPIC
  - [ ] IOAPIC
  - [ ] HPET
  - [ ] PIT
  - [ ] RTC
  - [ ] LAPIC Timer
  - [ ] Generic Timer
  - [ ] SMP
  - [ ] Scheduler x86_64
  - [ ] Scheduler aarch64

- **Modules and Drivers**
  - [ ] Modules x86_64
  - [ ] Modules aarch64
  - [ ] PS/2
  - [ ] AHCI
  - [ ] NVME
  - [ ] Block Device Interface
  - [ ] RTL8139
  - [ ] RTL8169
  - [ ] E1000 (100E 153A and 10EA)

- **Memory Management**
  - [ ] PMM
  - [ ] VMM (5 and 4 level)
  - [ ] Heap
  - [ ] MMAP

- **File Systems and Storage**
  - [ ] VFS
  - [ ] TMPFS
  - [ ] DEVTMPFS
  - [ ] PROCFS
  - [ ] SYSFS
  - [ ] USTAR
  - [ ] ILAR
  - [ ] EchFS
  - [ ] EXT2
  - [ ] FAT32

- **Networking**
  - [ ] Ethernet
  - [ ] ARP
  - [ ] IPv4
  - [ ] ICMPv4
  - [ ] TCP
  - [ ] UDP

- **Userspace and System Calls**
  - [ ] System calls x86_64
  - [ ] System calls aarch64
  - [ ] ELF
  - [ ] Userspace
  - [ ] Signals
  - [ ] mlibc

- **Device Interfaces**
  - [ ] TTY
  - [ ] PTY
  - [ ] CDEV
  - [ ] FBDEV

- **Permissions and Security**
  - [ ] Permissions
  - [ ] FDs

## Getting Started

### Requirements

- xmake
- clang/clang++
- lld
- llvm
- xorriso
- qemu-system-x86_64
- qemu-system-aarch64

#### Debian-based Systems

To install the required packages on Debian-based systems, run:

```sh
sudo apt install clang lld llvm xorriso qemu-system-x86 qemu-system-arm
```

#### xmake

To install xmake, run:

```sh
wget https://xmake.io/shget.text -O - | bash
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
