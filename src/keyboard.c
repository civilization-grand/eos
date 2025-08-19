
#include "keyboard.h"

int string_buffer_i = 0;
char caps_lock = 0;
char *string_buffer;

char scancode_translate(unsigned char scan_code)
{
    switch (scan_code)
    {
    case 0x39:
        return ' '; // Spacebar
    case 0x02:
        return '1';
    case 0x03:
        return '2';
    case 0x04:
        return '3';
    case 0x05:
        return '4';
    case 0x06:
        return '5';
    case 0x07:
        return '6';
    case 0x08:
        return '7';
    case 0x09:
        return '8';
    case 0x0A:
        return '9';
    case 0x0B:
        return '0';
    case 0x0C:
        return '-';
    case 0x0D:
        return '=';
    case 0x0E:
        return '\b'; // Backspace
    case 0x0F:
        return '\t'; // Tab
    case 0x10:
        return 'q';
    case 0x11:
        return 'w';
    case 0x12:
        return 'e';
    case 0x13:
        return 'r';
    case 0x14:
        return 't';
    case 0x15:
        return 'y';
    case 0x16:
        return 'u';
    case 0x17:
        return 'i';
    case 0x18:
        return 'o';
    case 0x19:
        return 'p';
    case 0x1A:
        return '[';
    case 0x1B:
        return ']';
    case 0x1C:
        return '\n'; // Enter
    case 0x1E:
        return 'a';
    case 0x1F:
        return 's';
    case 0x20:
        return 'd';
    case 0x21:
        return 'f';
    case 0x22:
        return 'g';
    case 0x23:
        return 'h';
    case 0x24:
        return 'j';
    case 0x25:
        return 'k';
    case 0x26:
        return 'l';
    case 0x27:
        return ';';
    case 0x28:
        return '\'';
    case 0x29:
        return '`';
    case 0x2B:
        return '\\';
    case 0x2C:
        return 'z';
    case 0x2D:
        return 'x';
    case 0x2E:
        return 'c';
    case 0x2F:
        return 'v';
    case 0x30:
        return 'b';
    case 0x31:
        return 'n';
    case 0x32:
        return 'm';
    case 0x33:
        return ',';
    case 0x34:
        return '.';
    case 0x35:
        return '/';
        /*----------------Control keys-------------*/
    case 0x36: // Right Shift
    {
        return 200;
        /*Handle procedure*/
    }
    case 0x2A: // Left Shift
    {
        /*Handle procedure*/
        return 201;
    }
    case 0x1D: // Left Ctrl
    {
        /*Handle procedure*/
        return 202;
    }
    case 0x38: // Left Alt
    {
        /*Handle procedure*/
        return 203;
    }
    case 0x3A: // Caps Lock
    {
        caps_lock = !caps_lock;
        return 204;
    }
    case 0x45: // Num Lock
    {
        /*Handle procedure*/
        return 205;
    }
    case 0x46: // Scroll Lock
    {
        /*Handle procedure*/
        return 206;
    }
        /*----------------Control keys-------------*/
    /*----------------Function keys-------------*/
    case 0x01:
        return 207; // Esc
    case 0x3B:
        return 208; // F1
    case 0x3C:
        return 209; // F2
    case 0x3D:
        return 210; // F3
    case 0x3E:
        return 211; // F4
    case 0x3F:
        return 212; // F5
    case 0x40:
        return 213; // F6
    case 0x41:
        return 214; // F7
    case 0x42:
        return 215; // F8
    case 0x43:
        return 216; // F9
    case 0x44:
        return 217; // F10
    /*----------------Function keys-------------*/

    /*--------------Keypad--------------*/
    case 0x47:
        return '7'; // Keypad 7
    case 0x48:
        return '8'; // Keypad 8
    case 0x49:
        return '9'; // Keypad 9
    case 0x4A:
        return '-'; // Keypad -
    case 0x4B:
        return '4'; // Keypad 4
    case 0x4C:
        return '5'; // Keypad 5
    case 0x4D:
        return '6'; // Keypad 6
    case 0x4E:
        return '+'; // Keypad +
    case 0x4F:
        return '1'; // Keypad 1
    case 0x50:
        return '2'; // Keypad 2
    case 0x51:
        return '3'; // Keypad 3
    case 0x52:
        return '0'; // Keypad 0
    case 0x37:
        return '*'; // Keypad *
    case 0x53:
        return '.'; // Keypad .
        /*--------------Keypad--------------*/
    default:
        return 0; // Unknown or unsupported key
    }
}

void handle_string_buffer(char scan_code)
{
    if (!(scan_code & 0x80)) // ignor the "release key"
    {
        char c;
        c = scancode_translate(scan_code);

        if (caps_lock == 1 && c != (char)204)
        {
            c -= 32;
        }

        if (c == (char)204)
        {
            return;
        }
        string_buffer_i++;
        string_buffer[string_buffer_i] = c;
        write_char(c, 0, 1);
        // fb_write(string_buffer, string_buffer_i);
    }
}