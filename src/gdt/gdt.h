
#ifndef _GDT_H
#define _GDT_H

struct gdt_entry
{
    /*Entry size = 64 bits*/
    unsigned short limit1;
    unsigned short base1;
    unsigned char base2;
    unsigned char access_byte;
    unsigned char flags;
    unsigned char base3;
} __attribute__((packed));

struct gdt
{
    /*GDT register value size = 48 bits*/
    unsigned short size;
    struct gdt_entry *address;
} __attribute__((packed));

void init_gdt();
void set_gdt_entry(unsigned int num, unsigned int base, unsigned limit, unsigned char access, unsigned char gran);

#endif