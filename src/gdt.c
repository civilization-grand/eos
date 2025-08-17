
#include "gdt.h"

extern void gdt_flush();

struct gdt_entry gdt_entries[5];
struct gdt gdt_ptr;

void init_gdt()
{
    gdt_ptr.size = (sizeof(struct gdt_entry) * 5) - 1;
    gdt_ptr.address = &gdt_entries[0];

    set_gdt_entry(0, 0, 0, 0, 0); // Null segment

    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel code segment
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel data segment

    set_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User code segment
    set_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User data segment

    gdt_flush(&gdt_ptr);
}

void set_gdt_entry(unsigned int num, unsigned int base, unsigned int limit, unsigned char access, unsigned char gran)
{
    gdt_entries[num].limit1 = (limit & 0xFFFF);
    gdt_entries[num].base1 = (base & 0xFFFF);
    gdt_entries[num].base2 = (base >> 16) & 0xFF;

    gdt_entries[num].access_byte = access;
    gdt_entries[num].flags = (limit >> 16) & 0x0F;
    gdt_entries[num].flags |= (gran & 0xF0);
    gdt_entries[num].base3 = (base >> 24) & 0xFF;
}
