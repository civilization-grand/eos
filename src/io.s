
global outb

outb:
    mov al, [esp + 8] ;data to send
    mov dx, [esp + 4] ;port number 
    out dx, al
    ret