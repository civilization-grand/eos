
#include "idt.h"
#include "io.h"
#include "vga.h"
#include "keyboard.h"

struct idt_entry entries[256];
struct idt idt_ptr;

extern string_buffer_i;
extern char *string_buffer;

extern void idt_flush(struct idt *idtp);

void set_idt_entry(unsigned int num, unsigned int handler, unsigned short segment, unsigned char flags)
{
    entries[num].base1 = handler & 0xFFFF;
    entries[num].segment_selector = segment;
    entries[num].reserved = 0;
    entries[num].flags = flags | 0x60;
    entries[num].base2 = (handler >> 16) & 0xFFFF;
}

void isr_handler(struct interrupt_registers *registers)
{

    char *m = "Fuken loser\n";
    fb_write(m, strlen(m));
    for (;;)
        ;
}

void irq_handler(struct interrupt_registers *registers)
{

    if (registers->int_no == 33)
    {
        unsigned char scan_code = inb(0x60);

        handle_string_buffer(scan_code);
    }

    outb(0x20, 0x20); //"acknowledgment" that the hardware interrupt must send. (interrupt handling complete).
}

void init_idt()
{
    idt_ptr.size = sizeof(struct idt_entry) * 256 - 1;
    idt_ptr.address = &entries[0];

    /*The two PIC chips (master/slave) must be initialized*/
    // First PIC chip: 0x20 for commands //0x21 for data
    // Second PIC chip: 0xA0 for commands //0xA1 for data

    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    outb(0x21, 0x00);
    outb(0xA1, 0x00);

    // Setting ISRs
    set_idt_entry(0, (unsigned int)isr0, 0x08, 0x8E);
    set_idt_entry(1, (unsigned int)isr1, 0x08, 0x8E);
    set_idt_entry(2, (unsigned int)isr2, 0x08, 0x8E);
    set_idt_entry(3, (unsigned int)isr3, 0x08, 0x8E);
    set_idt_entry(4, (unsigned int)isr4, 0x08, 0x8E);
    set_idt_entry(5, (unsigned int)isr5, 0x08, 0x8E);
    set_idt_entry(6, (unsigned int)isr6, 0x08, 0x8E);
    set_idt_entry(7, (unsigned int)isr7, 0x08, 0x8E);
    set_idt_entry(8, (unsigned int)isr8, 0x08, 0x8E);
    set_idt_entry(9, (unsigned int)isr9, 0x08, 0x8E);
    set_idt_entry(10, (unsigned int)isr10, 0x08, 0x8E);
    set_idt_entry(11, (unsigned int)isr11, 0x08, 0x8E);
    set_idt_entry(12, (unsigned int)isr12, 0x08, 0x8E);
    set_idt_entry(13, (unsigned int)isr13, 0x08, 0x8E);
    set_idt_entry(14, (unsigned int)isr14, 0x08, 0x8E);
    set_idt_entry(15, (unsigned int)isr15, 0x08, 0x8E);
    set_idt_entry(16, (unsigned int)isr16, 0x08, 0x8E);
    set_idt_entry(17, (unsigned int)isr17, 0x08, 0x8E);
    set_idt_entry(18, (unsigned int)isr18, 0x08, 0x8E);
    set_idt_entry(19, (unsigned int)isr19, 0x08, 0x8E);
    set_idt_entry(20, (unsigned int)isr20, 0x08, 0x8E);
    set_idt_entry(21, (unsigned int)isr21, 0x08, 0x8E);
    set_idt_entry(22, (unsigned int)isr22, 0x08, 0x8E);
    set_idt_entry(23, (unsigned int)isr23, 0x08, 0x8E);
    set_idt_entry(24, (unsigned int)isr24, 0x08, 0x8E);
    set_idt_entry(25, (unsigned int)isr25, 0x08, 0x8E);
    set_idt_entry(26, (unsigned int)isr26, 0x08, 0x8E);
    set_idt_entry(27, (unsigned int)isr27, 0x08, 0x8E);
    set_idt_entry(28, (unsigned int)isr28, 0x08, 0x8E);
    set_idt_entry(29, (unsigned int)isr29, 0x08, 0x8E);
    set_idt_entry(30, (unsigned int)isr30, 0x08, 0x8E);
    set_idt_entry(31, (unsigned int)isr31, 0x08, 0x8E);

    //-Setting IRQs
    set_idt_entry(32, (unsigned int)irq0, 0x08, 0x8E);
    set_idt_entry(33, (unsigned int)irq1, 0x08, 0x8E);
    set_idt_entry(34, (unsigned int)irq2, 0x08, 0x8E);
    set_idt_entry(35, (unsigned int)irq3, 0x08, 0x8E);
    set_idt_entry(36, (unsigned int)irq4, 0x08, 0x8E);
    set_idt_entry(37, (unsigned int)irq5, 0x08, 0x8E);
    set_idt_entry(38, (unsigned int)irq6, 0x08, 0x8E);
    set_idt_entry(39, (unsigned int)irq7, 0x08, 0x8E);
    set_idt_entry(40, (unsigned int)irq8, 0x08, 0x8E);
    set_idt_entry(41, (unsigned int)irq9, 0x08, 0x8E);
    set_idt_entry(42, (unsigned int)irq10, 0x08, 0x8E);
    set_idt_entry(43, (unsigned int)irq11, 0x08, 0x8E);
    set_idt_entry(44, (unsigned int)irq12, 0x08, 0x8E);
    set_idt_entry(45, (unsigned int)irq13, 0x08, 0x8E);
    set_idt_entry(46, (unsigned int)irq14, 0x08, 0x8E);
    set_idt_entry(47, (unsigned int)irq15, 0x08, 0x8E);

    idt_flush(&idt_ptr);
}