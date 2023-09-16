CPPPARAMS =  -s -Iinclude -nostdlib -fno-builtin -fno-exceptions -fno-leading-underscore -Wno-write-strings -fno-pic -ffreestanding -Wl,--build-id=none 
ASPARAMS	= -f elf64
LDPARAMS = -melf_x86_64

objects = 	obj/boot/header.o \
			obj/boot/main.o \
			obj/boot/main64.o \
			obj/drivers/io/ports.o \
			obj/drivers/serial/serial.o \
			obj/drivers/display/vga.o \
			obj/utils/log.o \
			obj/klib/stdio.o \
			obj/klib/string.o \
			obj/kernel.o 

ISO_FILENAME = dist/test_os.iso

obj/%.o: src/%.c
	mkdir -p $(@D)
	x86_64-elf-gcc $(CPPPARAMS) -o $@ -c $<

obj/%.o: src/%.S
	mkdir -p $(@D)
	nasm $(ASPARAMS) $< -o $@

kernel.elf: linker.ld $(objects)
	mkdir -p image
	x86_64-elf-ld -n -o $(LDPARAMS) -T $< -o image/$@ $(objects)

all: clean build run 
.PHONY: build

build: kernel.elf
	cp image/kernel.elf iso/boot/kernel.elf
	mkdir -p dist
	grub-mkrescue -o $(ISO_FILENAME) iso
	
clean:
	rm -rf obj image/kernel.elf $(ISO_FILENAME)

run:
	qemu-system-x86_64.exe -cdrom $(ISO_FILENAME) -serial file:"serial.log"

buildRun: build run