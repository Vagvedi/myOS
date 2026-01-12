# Makefile for minimal x86-32 kernel
# Target: QEMU with Multiboot support

# Compiler and flags
CC = gcc
AS = gcc
LD = ld

# Flags for freestanding C (no libc, no OS assumptions)
CFLAGS = -m32 -ffreestanding -nostdlib -nostdinc -Wall -Wextra -std=c11
ASFLAGS = -m32 -c  # Use GCC (GAS) for assembly files
LDFLAGS = -m elf_i386 -T linker.ld

# Source files
KERNEL_SOURCES = kernel.c
BOOT_SOURCES = boot.s
OBJS = $(BOOT_SOURCES:.s=.o) $(KERNEL_SOURCES:.c=.o)

# Output files
KERNEL = kernel.bin
ISO = myOS.iso

# Default target
all: $(KERNEL)

# Build kernel binary
$(KERNEL): $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble ASM files (using GCC which uses GAS)
%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

# Create ISO for QEMU (requires grub-mkrescue)
iso: $(KERNEL)
	mkdir -p isodir/boot/grub
	cp $(KERNEL) isodir/boot/
	cp grub.cfg isodir/boot/grub/
	grub-mkrescue -o $(ISO) isodir

# Run in QEMU (direct multiboot, no ISO needed)
run: $(KERNEL)
	qemu-system-i386 -kernel $(KERNEL)

# Clean build artifacts
clean:
	rm -f $(OBJS) $(KERNEL) $(ISO)
	rm -rf isodir

.PHONY: all iso run clean
