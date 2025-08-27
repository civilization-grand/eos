

OBJECT_FILES = objects/loader.o objects/kmain.o objects/vga.o objects/io.o objects/gdt.o objects/gdts.o objects/idt.o objects/idts.o objects/keyboard.o objects/string.o objects/memory.o objects/kheap.o objects/stdio.o objects/shell.o
GCC_FLAGS = -m32 -nostdlib -fno-builtin  -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -g -c 
INCLUDES = -I./src

iso/boot/kernel.elf: $(OBJECT_FILES)
	ld -T src/link.ld -melf_i386 $(OBJECT_FILES) -o iso/boot/kernel.elf

objects/loader.o: src/loader.s
	nasm -f elf32 -g src/loader.s -o objects/loader.o

objects/kmain.o: src/kmain.c
	gcc $(INCLUDES) $(GCC_FLAGS) src/kmain.c -o objects/kmain.o

objects/vga.o: src/vga/vga.c
	gcc $(INCLUDES) $(GCC_FLAGS) src/vga/vga.c -o objects/vga.o

objects/io.o: src/io/io.s
	nasm -f elf32 -g src/io/io.s -o objects/io.o

objects/gdts.o: src/gdt/gdts.s
	nasm -f elf32 -g src/gdt/gdts.s -o objects/gdts.o

objects/gdt.o: src/gdt/gdt.c
	gcc $(INCLUDES) $(GCC_FLAGS) src/gdt/gdt.c -o objects/gdt.o

objects/idts.o: src/idt/idts.asm
	nasm -f elf32 -g src/idt/idts.asm -o objects/idts.o

objects/idt.o: src/idt/idt.c
	gcc $(INCLUDES) $(GCC_FLAGS) src/idt/idt.c -o objects/idt.o

objects/keyboard.o: src/keyboard/keyboard.c
	gcc $(INCLUDES) $(GCC_FLAGS) src/keyboard/keyboard.c -o objects/keyboard.o

objects/string.o: src/string/string.c
	gcc $(INCLUDES) $(GCC_FLAGS) src/string/string.c -o objects/string.o

objects/memory.o: src/memory/memory.c
	gcc $(INCLUDES) $(GCC_FLAGS) src/memory/memory.c -o objects/memory.o

objects/kheap.o: src/memory/heap/kheap.c
	gcc $(INCLUDES) $(GCC_FLAGS) src/memory/heap/kheap.c -o objects/kheap.o

objects/stdio.o: src/stdio/stdio.c
	gcc $(INCLUDES) $(GCC_FLAGS) src/stdio/stdio.c -o objects/stdio.o

objects/shell.o: src/shell/shell.c
	gcc $(INCLUDES) $(GCC_FLAGS) src/shell/shell.c -o objects/shell.o

iso: iso/boot/grub/stage2_eltorito
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o eos.iso iso

emu_elf:
	qemu-system-i386 -kernel iso/boot/kernel.elf -s -S

emu: eos.iso
	qemu-system-x86_64 -cdrom eos.iso

clean:
	rm -rf objects/*.o iso/boot/kernel.elf eos.iso