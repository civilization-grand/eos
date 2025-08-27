#include "stdio.h"
#include "keyboard/keyboard.h"
#include "vga/vga.h"

char read_char()
{

    char c;
    while (!key_ready)
        ;

    key_ready = 0;
    if (caps_lock == 1)
    {
        c = scancode_to_ascii[key];
        c -= 32;
        write_char(c, 0, DARK_GRAY);
        return c;
    }

    c = scancode_to_ascii[key];
    write_char(c, 0, DARK_GRAY);

    return c;
}

void read_string(char string[INPUT_BUFFER_MAX_SIZE])
{
    int i = 0;
    char c;
    while (1)
    {
        string[i] = read_char();

        while (string[i] == '\b')
        {
            if (i == 0)
            {
                break;
            }

            i -= 1;
            string[i] = read_char();
        }

        if (string[0] == '\b')
        {
            break;
        }

        if (string[i] == '\n')
        {
            break;
        }

        i++;
    }
    string[i + 1] = '\0';
    return string;
}

void print(char string[INPUT_BUFFER_MAX_SIZE])
{
    fb_write(string, strlen(string), 0, LIGHT_GRAY);
}
