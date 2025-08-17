#include "io.h"
#include "gdt.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 20

char *fb = (char *)0x000b8000;
unsigned short console_rows;
unsigned short console_cols;

int cp = 0;
int x = 0;
int y = 0;

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

        return;
    }

    write_cell((cp * 2), c, fg, bg);
    cp++;
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

int strlen(char *str)
{
    int size = 0;
    while (str[size] != '\0')
    {
        size++;
    }
    return size;
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

void kmain()
{
    console_init();

    char *os_name = "                           <<-GG Operating system->>\n\n";
    fb_write(os_name, strlen(os_name));

    init_gdt();

    char *gdt_msg = "GDT: Everything is fine.\n\n";
    fb_write(gdt_msg, strlen(gdt_msg));

    char *os_msg = "Someone was blessed with a new baby, and he asked the obstetrician: Does it have a brain?\nThe doctor replied, surprised : What makes you wonder about that?\nThe man : No !I want it without a brain !\nThe doctor : Why?\nThe man: That's our custom... We remove our brains, so we obey our parents, and they, who lack brains, in turn obey their parents, and so on until obedience finally leads to something no one knows about.";
    fb_write(os_msg, strlen(os_msg));

    mov_cursor(cp);
}