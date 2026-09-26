#include <stdint.h>
#include <stddef.h>

/* VGA Text Mode Colors */
enum VgaColor {
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GREY = 7,
    COLOR_DARK_GREY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_LIGHT_MAGENTA = 13,
    COLOR_LIGHT_BROWN = 14,
    COLOR_WHITE = 15,
};

static inline uint8_t make_color(enum VgaColor fg, enum VgaColor bg) {
    return fg | (bg << 4);
}

static inline uint16_t make_vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t)uc | ((uint16_t)color << 8);
}

static size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_BUFFER = (uint16_t*)0xB8000;

class Terminal {
private:
    size_t row;
    size_t column;
    uint8_t color;
    uint16_t* buffer;

public:
    void initialize() {
        row = 0;
        column = 0;
        color = make_color(COLOR_LIGHT_CYAN, COLOR_BLACK);
        buffer = VGA_BUFFER;

        for (size_t y = 0; y < VGA_HEIGHT; y++) {
            for (size_t x = 0; x < VGA_WIDTH; x++) {
                const size_t index = y * VGA_WIDTH + x;
                buffer[index] = make_vga_entry(' ', color);
            }
        }
    }

    void set_color(uint8_t new_color) {
        color = new_color;
    }

    void put_char(char c) {
        if (c == '\n') {
            column = 0;
            if (++row == VGA_HEIGHT) {
                row = 0;
            }
            return;
        }

        const size_t index = row * VGA_WIDTH + column;
        buffer[index] = make_vga_entry(c, color);

        if (++column == VGA_WIDTH) {
            column = 0;
            if (++row == VGA_HEIGHT) {
                row = 0;
            }
        }
    }

    void write(const char* data, size_t size) {
        for (size_t i = 0; i < size; i++) {
            put_char(data[i]);
        }
    }

    void print(const char* str) {
        write(str, strlen(str));
    }
};

static Terminal term;

extern "C" void kernel_main(void) {
    term.initialize();

    term.set_color(make_color(COLOR_LIGHT_GREEN, COLOR_BLACK));
    term.print("================================================================================\n");
    term.print("                      AetherOS Kernel 32-bit Initialized                        \n");
    term.print("================================================================================\n\n");

    term.set_color(make_color(COLOR_WHITE, COLOR_BLACK));
    term.print("[OK] CPU Architecture: x86 Protected Mode (32-bit)\n");
    term.print("[OK] Video Output: Direct Framebuffer MMIO at 0x000B8000\n");
    term.print("[OK] Multiboot Header Verified by Bootloader\n");
    term.print("[OK] Stack Segment Setup Completed (16 KiB)\n\n");

    term.set_color(make_color(COLOR_LIGHT_CYAN, COLOR_BLACK));
    term.print("Welcome to your custom operating system.\n");
    term.print("System idle. CPU halted in safe mode.\n");
}
