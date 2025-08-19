#include "io.h"
#include "gdt.h"
#include "idt.h"
#include "vga.h"
#include "string.h"

extern int cp;
extern int string_buffer;
int shell_index;

void kmain()
{
    console_init();

    char *os_name = "                         <<-An operating system is running->>\n\n";
    fb_write(os_name, strlen(os_name));

    init_gdt();

    char *gdt_msg = "GDT: Everything is fine.\n";
    fb_write(gdt_msg, strlen(gdt_msg));

    init_idt();

    char *idt_msg = "IDT: Everything is fine.\n";
    fb_write(idt_msg, strlen(idt_msg));

    char *copy = "IDT: Everything is fine-------------------.\n";
    strcpy(copy, idt_msg);
    fb_write(copy, strlen(copy));

    if (strcmp(idt_msg, copy))
    {
        char *is_equ = "They are same\n";
        fb_write(is_equ, strlen(is_equ));
    }

    // int x = 1 / 0;

    char *shell_msg = ">>";
    fb_write(shell_msg, strlen(shell_msg));
    shell_index = cp;
}