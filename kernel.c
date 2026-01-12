/* Minimal x86-32 kernel - VGA text mode output
 * 
 * VGA text buffer:
 * - Address: 0xB8000
 * - 80 columns x 25 rows
 * - Each character: 2 bytes (char + attribute)
 * - Attribute byte: background (4 bits) + foreground (4 bits)
 * - Colors: 0=black, 1=blue, 2=green, 3=cyan, 4=red, 5=magenta, 6=brown, 7=light gray
 *           8=dark gray, 9=light blue, 10=light green, 11=light cyan, 12=light red,
 *           13=light magenta, 14=yellow, 15=white
 */

/* Multiboot header structure (simplified) */
struct multiboot_info {
    unsigned int flags;
    unsigned int mem_lower;
    unsigned int mem_upper;
    // ... (we only need flags and memory for now)
};

/* VGA text buffer */
#define VGA_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

/* Color constants */
#define COLOR_BLACK 0
#define COLOR_LIGHT_GRAY 7
#define COLOR_LIGHT_GREEN 10
#define COLOR_WHITE 15

/* Calculate color attribute byte */
#define COLOR_ATTR(fg, bg) ((bg << 4) | fg)

/* Current cursor position */
static unsigned int cursor_row = 0;
static unsigned int cursor_col = 0;

/* Write a character to VGA buffer */
static void vga_putchar(char c, unsigned char color) {
    volatile char *video = (volatile char *)VGA_ADDRESS;
    
    if (c == '\n') {
        cursor_row++;
        cursor_col = 0;
    } else if (c == '\t') {
        cursor_col = (cursor_col + 4) & ~(4 - 1);  /* Align to 4 */
    } else {
        unsigned int pos = (cursor_row * VGA_WIDTH + cursor_col) * 2;
        video[pos] = c;
        video[pos + 1] = color;
        cursor_col++;
    }
    
    /* Wrap to next line if needed */
    if (cursor_col >= VGA_WIDTH) {
        cursor_col = 0;
        cursor_row++;
    }
    
    /* Scroll if we've reached the bottom */
    if (cursor_row >= VGA_HEIGHT) {
        /* Simple scroll: move all lines up by one */
        volatile char *src = (volatile char *)(VGA_ADDRESS + VGA_WIDTH * 2);
        volatile char *dst = (volatile char *)VGA_ADDRESS;
        unsigned int bytes = (VGA_HEIGHT - 1) * VGA_WIDTH * 2;
        for (unsigned int i = 0; i < bytes; i++) {
            dst[i] = src[i];
        }
        /* Clear last line */
        for (unsigned int col = 0; col < VGA_WIDTH; col++) {
            unsigned int pos = ((VGA_HEIGHT - 1) * VGA_WIDTH + col) * 2;
            video[pos] = ' ';
            video[pos + 1] = COLOR_ATTR(COLOR_WHITE, COLOR_BLACK);
        }
        cursor_row = VGA_HEIGHT - 1;
    }
}

/* Clear the screen */
static void vga_clear(void) {
    volatile char *video = (volatile char *)VGA_ADDRESS;
    unsigned char color = COLOR_ATTR(COLOR_WHITE, COLOR_BLACK);
    
    for (unsigned int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        video[i * 2] = ' ';
        video[i * 2 + 1] = color;
    }
    
    cursor_row = 0;
    cursor_col = 0;
}

/* Print a string */
static void vga_print(const char *str) {
    unsigned char color = COLOR_ATTR(COLOR_LIGHT_GREEN, COLOR_BLACK);
    
    while (*str) {
        vga_putchar(*str++, color);
    }
}

/* Kernel entry point (called from boot.s) */
void kernel_main(unsigned int magic, struct multiboot_info *mb_info) {
    /* Clear screen */
    vga_clear();
    
    /* Print greeting */
    vga_print("myOS v0.1 - Minimal x86-32 Kernel\n");
    vga_print("Multiboot magic: 0x");
    
    /* Print magic number in hex (simple version) */
    char hex_digits[] = "0123456789ABCDEF";
    unsigned char color = COLOR_ATTR(COLOR_LIGHT_GREEN, COLOR_BLACK);
    for (int i = 28; i >= 0; i -= 4) {
        unsigned char digit = (magic >> i) & 0xF;
        vga_putchar(hex_digits[digit], color);
    }
    vga_print("\n");
    
    if (magic == 0x2BADB002) {
        vga_print("Multiboot signature: VALID\n");
        if (mb_info->flags & 0x01) {
            vga_print("Memory info available\n");
            vga_print("Lower memory: ");
            /* Simple number printing (very basic) */
            unsigned int mem_lower = mb_info->mem_lower;
            if (mem_lower == 0) {
                vga_putchar('0', color);
            } else {
                char temp[16];
                int temp_idx = 0;
                while (mem_lower > 0) {
                    temp[temp_idx++] = '0' + (mem_lower % 10);
                    mem_lower /= 10;
                }
                for (int i = temp_idx - 1; i >= 0; i--) {
                    vga_putchar(temp[i], color);
                }
            }
            vga_print(" KB\n");
        }
    } else {
        vga_print("ERROR: Invalid Multiboot signature!\n");
    }
    
    vga_print("\nKernel is running...\n");
    
    /* Infinite loop - kernel should never return */
    while (1) {
        __asm__ volatile ("hlt");
    /* Halt CPU until interrupt */
    }
}
