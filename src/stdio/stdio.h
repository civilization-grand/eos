
#ifndef STDIO_H
#define STDIO_H

#define INPUT_BUFFER_MAX_SIZE 512

extern char scancode_to_ascii[128];
extern unsigned char key;
extern unsigned char key_ready;

char read_char();
void read_string(char string[INPUT_BUFFER_MAX_SIZE]);

#endif
