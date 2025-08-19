global loader
extern kmain

MAGIC_NUMBER    equ 0x1badb002
FLAGS           equ 0x0
CHECKSUM        equ -MAGIC_NUMBER     

KERNEL_STACK_SIZE equ 4096

section .text
align 4 ;Tells the assembler: "Make sure the next data is stored at an address that's a multiple of 4."
dd MAGIC_NUMBER
dd FLAGS
dd CHECKSUM

loader:
;mov eax, 0xcafebabe
;mov word [0x000b8000], 0x2841

cli

mov esp, kernel_stack + KERNEL_STACK_SIZE

call kmain

.loop:
jmp .loop

section .bss
align 4
kernel_stack:
resb KERNEL_STACK_SIZE
