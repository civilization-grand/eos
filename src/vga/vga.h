
#ifndef _VGA_H
#define _VGA_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VIDEO_MEMORY_ADDRESS 0x000b8000

#define BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define CYAN 0x3
#define RED 0x4
#define MAGENTA 0x5
#define BROWN 0x6
#define LIGHT_GRAY 0x7
#define DARK_GRAY 0x8
#define LIGHT_BLUE 0x9
#define LIGHT_GREEN 0xA
#define LIGHT_CYAN 0xB
#define LIGHT_RED 0xC
#define LIGHT_MAGENTA 0xD
#define YELLOW 0xE
#define WHITE 0xF

void write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
void write_char(char c, unsigned char fg, unsigned char bg);
void mov_cursor(int pos);
void fb_write(char *buf, int len, unsigned char fg, unsigned char bg);
void scroll_screen();
void init_console();

#endif