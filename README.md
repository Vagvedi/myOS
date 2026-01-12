# myOS - Minimal x86-32 Educational Operating System

A minimal but real x86 32-bit operating system built for educational purposes.

## Architecture

- **CPU**: x86 (IA-32, 32-bit)
- **Bootloader**: GRUB (Multiboot v1 specification)
- **Language**: Freestanding C + x86 Assembly
- **Target**: QEMU emulator

## Building

### Prerequisites

- GCC with 32-bit support: `gcc-multilib` (Linux) or `mingw-w64` (Windows)
- NASM assembler
- LD (linker)
- QEMU: `qemu-system-i386`
- GRUB tools (for ISO creation): `grub-pc-bin` or `grub2`

### Build

```bash
make
```

This creates `kernel.bin`.

### Run in QEMU

```bash
make run
```

Or directly:
```bash
qemu-system-i386 -kernel kernel.bin
```

### Create ISO (optional)

```bash
make iso
qemu-system-i386 -cdrom myOS.iso
```

## Current Status

**Step 1**: Minimal Multiboot-compliant kernel with VGA text output

## Files

- `boot.s`: Multiboot header and kernel entry point (assembly)
- `kernel.c`: Main kernel code with VGA text output
- `linker.ld`: Linker script (ensures Multiboot header at start)
- `Makefile`: Build configuration
- `grub.cfg`: GRUB configuration (for ISO)

## Next Steps

1. GDT (Global Descriptor Table)
2. IDT (Interrupt Descriptor Table)
3. IRQ handling
4. Timer interrupt
5. Task scheduler
6. Paging
7. System calls
8. Basic shell
