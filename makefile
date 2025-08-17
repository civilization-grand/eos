

OBJECT_FILES = objects/loader.o objects/kmain.o objects/io.o objects/gdt.o objects/gdts.o
GCC_FLAGS = -m32 -nostdlib -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c


iso/boot/kernel.elf: $(OBJECT_FILES)
	ld -T src/link.ld -melf_i386 $(OBJECT_FILES) -o iso/boot/kernel.elf

objects/loader.o: src/loader.s
	nasm -f elf32 src/loader.s -o objects/loader.o

objects/kmain.o: src/kmain.c
	gcc $(GCC_FLAGS) src/kmain.c -o objects/kmain.o

objects/io.o: src/io.s
	nasm -f elf32 src/io.s -o objects/io.o

objects/gdts.o: src/gdts.s
	nasm -f elf32 src/gdts.s -o objects/gdts.o

objects/gdt.o: src/gdt.c
	gcc $(GCC_FLAGS) src/gdt.c -o objects/gdt.o

iso: iso/boot/grub/stage2_eltorito
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o os.iso iso

emu: os.iso
	qemu-system-x86_64 -cdrom os.iso

clean:
	rm -rf objects/*.o iso/boot/kernel.elf os.iso