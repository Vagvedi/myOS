/* x86 32-bit Multiboot-compliant boot entry point
 * 
 * Multiboot v1 specification:
 * - Magic number: 0x1BADB002
 * - Header must be in first 8KB of kernel
 * - Flags: page-aligned modules (1), memory info (2), video info (4)
 * - Checksum: -(magic + flags)
 */

.section .multiboot
.align 4
multiboot_header:
    .long 0x1BADB002      /* Magic number */
    .long 0x00000003      /* Flags: page-aligned modules (1) + memory info (2) */
    .long -(0x1BADB002 + 0x00000003)  /* Checksum */

/* Stack setup (16-byte aligned for x86-32) */
.section .bss
.align 16
stack_bottom:
    .skip 16384           /* 16KB stack */
stack_top:

/* Kernel entry point */
.section .text
.global _start
.type _start, @function
_start:
    /* Set up stack pointer */
    mov $stack_top, %esp
    
    /* Clear direction flag (std -> cld) */
    cld
    
    /* Push Multiboot info structure (passed by GRUB in EBX) */
    push %ebx
    /* Push Multiboot magic number (passed by GRUB in EAX) */
    push %eax
    
    /* Call C kernel entry point */
    call kernel_main
    
    /* If kernel_main returns, halt */
    cli
halt_loop:
    hlt
    jmp halt_loop

.size _start, . - _start
