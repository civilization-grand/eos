
#include "vga.h"
#include "io/io.h"

extern int shell_cursor;

char *fb = (char *)VIDEO_MEMORY_ADDRESS;
unsigned short console_rows;
unsigned short console_cols;

int cp = 0;
int y = 0;
int x = 0;

void write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{

    fb[i] = c;
    fb[i + 1] = ((fg & 0x0f /*extract the lower 4 bits*/) << 4) | (bg & 0x0f);
}

void write_char(char c, unsigned char fg, unsigned char bg)
{
    if (y == VGA_HEIGHT)
    {
        scroll_screen();
    }

    if (c == '\n')
    {
        y += 1;
        cp = (y * VGA_WIDTH);
        mov_cursor(cp);
        return;
    }

    if (c == '\b')
    {
        if (cp == shell_cursor)
        {
            return;
        }

        cp--;
        mov_cursor(cp);
        write_cell((cp * 2), ' ', fg, bg);
        return;
    }

    write_cell((cp * 2), c, fg, bg);
    cp++;

    y = cp / VGA_WIDTH;

    mov_cursor(cp);
}

void mov_cursor(int pos)
{
    unsigned char high_byte = ((pos >> 8) & 0x00FF); // extracting the high byte
    unsigned char low_byte = pos & 0x00FF;           // extracting the low byte

    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, high_byte);
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, low_byte);
}

void fb_write(char *buf, int len, unsigned char fg, unsigned char bg)
{
    for (int i = 0; i < len; i++)
    {
        write_char(buf[i], fg, bg);
    }
}

void scroll_screen()
{
    int from;
    int to;

    for (int line = 0; line < VGA_HEIGHT; line++)
    {
        for (int col = 0; col < VGA_WIDTH; col++)
        {
            int from = (line * VGA_WIDTH + col) * 2;
            int to = ((line - 1) * VGA_WIDTH + col) * 2;

            fb[to] = fb[from];
            fb[to + 1] = fb[from + 1];
        }
    }

    int bottom_line = (VGA_HEIGHT - 1) * VGA_WIDTH;
    for (int col = 0; col < VGA_WIDTH; col++)
    {
        write_cell((bottom_line + col) * 2, ' ', BLACK, WHITE);
    }

    y = VGA_HEIGHT - 1;
    cp = (y * VGA_WIDTH);
    mov_cursor(cp);
}

void init_console()
{
    for (int i = 0; i < VGA_HEIGHT; i++)
    {
        for (int j = 0; j < VGA_WIDTH; j++)
        {
            write_char(' ', BLACK, WHITE);
        }
    }

    cp = 0;
    y = 0;
    mov_cursor(cp);
}
