
global outb

outb:
    mov al, [esp + 8] ;data to send
    mov dx, [esp + 4] ;port number 
    out dx, al
    ret

global inb
inb:
    mov dx, [esp + 4]  ; Port number
    in al, dx          ; Read byte from port (data will be stored at al)
    ret