#ifndef _IDT_H
#define _IDT_H

struct idt_entry
{
    unsigned short base1;
    unsigned short segment_selector;
    unsigned char reserved;
    unsigned char flags;
    unsigned short base2;
} __attribute__((packed));

struct idt
{
    unsigned short size;
    unsigned int address;
} __attribute__((packed));

void zero_divide_int();       // isr0
void double_fault_int();      // isr8
void timer_int();             // irq0
unsigned char keyboard_int(); // irq1

// ISRs
extern void isr0(); // divition by zero

// extern void isr1();
// extern void isr2();
// extern void isr3();
// extern void isr4();
// extern void isr5();
// extern void isr6();
// extern void isr7();
extern void isr8(); // double fault
// extern void isr9();
// extern void isr10();
// extern void isr11();
// extern void isr12();
// extern void isr13();
// extern void isr14();
// extern void isr15();
// extern void isr16();
// extern void isr17();
// extern void isr18();
// extern void isr19();
// extern void isr20();
// extern void isr21();
// extern void isr22();
// extern void isr23();
// extern void isr24();
// extern void isr25();
// extern void isr26();
// extern void isr27();
// extern void isr28();
// extern void isr29();
// extern void isr30();
// extern void isr31();

// IRQs

extern void irq0(); // timer
extern void irq1(); // keyboard

// extern void irq2();
// extern void irq3();
// extern void irq4();
// extern void irq5();
// extern void irq6();
// extern void irq7();
// extern void irq8();
// extern void irq9();
// extern void irq10();
// extern void irq11();
// extern void irq12();
// extern void irq13();
// extern void irq14();
// extern void irq15();

void init_idt();

#endif
