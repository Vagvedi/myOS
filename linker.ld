/* Linker script for x86 32-bit kernel
 * Multiboot specification requires:
 * - Header must be within first 8KB
 * - Kernel must be 32-bit
 * - Entry point must be at the beginning
 */

ENTRY(_start)

SECTIONS
{
    /* Kernel starts at 1MB (0x100000) - standard location */
    . = 0x100000;

    /* Multiboot header MUST be at the very beginning */
    .multiboot ALIGN(4) : {
        *(.multiboot)
    }

    /* Text section */
    .text : {
        *(.text)
    }

    /* Read-only data */
    .rodata : {
        *(.rodata)
    }

    /* Read-write data */
    .data : {
        *(.data)
    }

    /* Uninitialized data */
    .bss : {
        *(COMMON)
        *(.bss)
    }

    /* Discard everything else */
    /DISCARD/ : {
        *(.note.gnu.build-id)
    }
}
