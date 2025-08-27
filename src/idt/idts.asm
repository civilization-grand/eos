
global idt_flush
idt_flush:

    mov eax, [esp + 4]
    lidt[eax]

    sti
    ret
;-----------------------------------
;ISR0
extern zero_divide_int
global isr0
isr0:
    cli
    pushad
    call zero_divide_int
    popad
    sti
    iret

;ISR8
extern double_fault_int
global isr8
isr8:
    cli
    pushad
    call double_fault_int
    popad
    sti
    iret
;-----------------------------------
;IRQ0
extern timer_int
global irq0
irq0:
    cli
    pushad
    call timer_int
    popad
    sti
    iret

;IRQ1
extern keyboard_int
global irq1
irq1:
    cli
    pushad
    call keyboard_int
    popad
    sti
    iret
;--------------------------------------

extern no_int_handler
no_int:
    cli
    pushad ;push eax, edx, ebx, original esp, ebp, esi, and edi
    call no_int_handler
    popad
    sti
    iret ;interrupt return


