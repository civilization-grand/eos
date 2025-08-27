#include "io/io.h"
#include "gdt/gdt.h"
#include "idt/idt.h"
#include "vga/vga.h"
#include "string/string.h"
#include "memory/heap/kheap.h"
#include "stdio/stdio.h"

#include "shell/shell.h"

void kmain()
{
    init_console();
    init_gdt();
    init_idt();
    init_pool();

    char *had_msg1 = "              @@@@@  @@@@@  @@@@@\n";
    char *had_msg2 = "              @      @   @  @    \n";
    char *had_msg3 = "              @@@@   @   @  @@@@@\n";
    char *had_msg4 = "              @      @   @      @\n";
    char *had_msg5 = "              @@@@@  @@@@@  @@@@@\n\n";
    char *had_msg6 = "       Type 'help' to see what you can do.\n\n";

    fb_write(had_msg1, strlen(had_msg1), 0, GREEN);
    fb_write(had_msg2, strlen(had_msg2), 0, GREEN);

    fb_write(had_msg3, strlen(had_msg3), 0, GREEN);
    fb_write(had_msg4, strlen(had_msg4), 0, GREEN);
    fb_write(had_msg5, strlen(had_msg5), 0, GREEN);
    fb_write(had_msg6, strlen(had_msg6), 0, GREEN);

    /*
    char *had_msg1_2 = "      eos\n";
    char *had_msg2_2 = "     e   e \n";
    char *had_msg3_2 = "    o <0> o \n";
    char *had_msg4_2 = "   s       s \n";
    char *had_msg5_2 = "  eos_eos_eos \n";
    */

    /*
    char *msg = "---Read it, feel it, then criticize it--\nThese might be the words that can ruin my life,\nand yours too if you wasn't wise enough,\nsince a few words was enough to crush somone,\nor make him bleed forever.\n";
    fb_write(msg, strlen(msg));
    */

    shell_main();
}