
#ifndef _VGA_H
#define _VGA_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 20

void write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
void write_char(char c, unsigned char fg, unsigned char bg);
void mov_cursor(int pos);

int strlen(char *str);

void fb_write(char *buf, int len);

void console_init();

void serial_configure_baud_rate(unsigned short com, unsigned short divisor);

void serial_configure_line(unsigned short com);
#endif