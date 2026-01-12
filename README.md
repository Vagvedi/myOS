# 🖥️ myOS - Minimal x86-32 Educational Operating System

A minimal but fully functional x86 32-bit operating system built from scratch for educational purposes. This project demonstrates core OS concepts including bootloading, kernel initialization, and low-level hardware interaction.

---

## 📋 Quick Start

```bash
# Build the kernel
make

# Run in QEMU
make run

# Create and boot from ISO
make iso
qemu-system-i386 -cdrom myOS.iso
```

---

## 🏗️ Architecture Overview

| Component | Details |
|-----------|---------|
| **CPU** | x86 (IA-32, 32-bit) |
| **Bootloader** | GRUB (Multiboot v1 specification) |
| **Languages** | Freestanding C + x86 Assembly |
| **Execution Environment** | QEMU emulator |
| **Memory Model** | Protected mode, flat memory model |

---

## 📦 Prerequisites

Ensure you have the following tools installed:

- **GCC with 32-bit support**
  - Linux: `gcc-multilib`
  - Windows: `mingw-w64`
- **NASM assembler** - for assembly compilation
- **LD linker** - comes with binutils
- **QEMU** - `qemu-system-i386` for emulation
- **GRUB tools** - `grub-pc-bin` or `grub2` (for ISO creation)

### Installation (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install build-essential gcc-multilib nasm qemu-system-x86 grub-pc-bin xorriso
```

---

## 🔨 Building & Running

### Build the Kernel

```bash
make
```

This compiles the assembly and C code, links them with the linker script, and produces `kernel.bin`.

### Run in QEMU (Simplest Method)

```bash
make run
```

Or manually:

```bash
qemu-system-i386 -kernel kernel.bin
```

### Create Bootable ISO

```bash
make iso
qemu-system-i386 -cdrom myOS.iso
```

### Clean Build Artifacts

```bash
make clean
```

---

## 📁 Project Structure

| File | Purpose |
|------|---------|
| `boot.s` | Multiboot header and kernel entry point (x86 assembly) |
| `kernel.c` | Main kernel implementation with VGA text output |
| `linker.ld` | Linker script ensuring proper memory layout |
| `Makefile` | Build automation and targets |
| `grub.cfg` | GRUB bootloader configuration |

---

## 🚀 Current Implementation

### ✅ Completed Features

- **Multiboot Compliance**: GRUB-compatible bootable kernel
- **Protected Mode**: CPU running in 32-bit protected mode
- **VGA Text Output**: Direct video memory manipulation for printing
- **Basic Kernel Loop**: Infinite loop after initialization

### 📊 Development Roadmap

The project follows a structured progression toward a feature-complete OS:

1. ⬜ **GDT** (Global Descriptor Table) - Memory segmentation
2. ⬜ **IDT** (Interrupt Descriptor Table) - Exception handling
3. ⬜ **IRQ Handling** - Hardware interrupt processing
4. ⬜ **Timer Interrupt** - Preemptive multitasking foundation
5. ⬜ **Task Scheduler** - Context switching and process management
6. ⬜ **Paging** - Virtual memory management
7. ⬜ **System Calls** - User-mode kernel interface
8. ⬜ **Basic Shell** - Command-line interface

---

## 💡 Educational Value

This project is ideal for learning:

- **Low-level OS design** - Direct hardware interaction
- **x86 assembly** - CPU instruction set and calling conventions
- **Memory management** - Segmentation, paging, and virtual memory
- **Bootloading** - How operating systems start up
- **Interrupt handling** - Exception and signal processing
- **Multiprocessing** - Task scheduling and context switching

---

## 🔗 Resources

- [OSDev Wiki](https://wiki.osdev.org/) - Comprehensive OS development reference
- [Intel x86 Manuals](https://www.intel.com/content/www/us/en/develop/articles/intel-sdm.html)
- [Multiboot Specification](https://www.gnu.org/software/grub/manual/multiboot/multiboot.html)
- [QEMU Documentation](https://www.qemu.org/documentation/)

---

## 📝 License

Educational project - free to use and modify for learning purposes.
