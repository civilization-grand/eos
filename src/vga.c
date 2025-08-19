
#include "vga.h"
#include "io.h"

char *fb = (char *)0x000b8000;
unsigned short console_rows;
unsigned short console_cols;

int cp = 0;
int x = 0;
int y = 0;

extern int shell_index;

void write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0f /*extract the lower 4 bits*/) << 4) | (bg & 0x0f);
}

void write_char(char c, unsigned char fg, unsigned char bg)
{

    if (c == '\n')
    {
        y += 1;
        cp = (y * VGA_WIDTH);
        mov_cursor(cp);
        return;
    }

    if (c == '\b')
    {
        if (cp == shell_index)
        {
            return;
        }
        cp--;
        write_cell((cp * 2), ' ', fg, bg);
        mov_cursor(cp);
        return;
    }

    write_cell((cp * 2), c, fg, bg);
    cp++;

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

void fb_write(char *buf, int len)
{
    for (int i = 0; i < len; i++)
    {
        write_char(buf[i], 0, 6);
    }
}

void console_init()
{
    for (int i = 0; i < VGA_HEIGHT; i++)
    {
        for (int j = 0; j < VGA_WIDTH; j++)
        {
            write_char(' ', 0, 7);
        }
    }

    cp = 0;
}

void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

void serial_configure_line(unsigned short com)
{
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}
