#CPPPARAMS =  -s -Iinclude -nostdlib -fno-builtin -fno-exceptions -fno-leading-underscore -Wno-write-strings -fno-pic -ffreestanding -Wl,--build-id=none 
CPPPARAMS := -std=gnu99 \
		-nostdlib \
		-fno-builtin \
		-fno-exceptions \
		-fno-leading-underscore \
		-Wno-write-strings \
		-fno-pic \
		-ffreestanding \
        -ffreestanding \
        -Wall \
        -Wextra \
        -Iinclude \
        -mno-red-zone \
        -mno-sse \
        -mcmodel=large

ASPARAMS	= -f elf64
LDPARAMS = -melf_x86_64
QEMU_SYSTEM := qemu-system-x86_64.exe

objects = 	obj/boot/main.o \
			obj/drivers/io/ports.o \
			obj/drivers/serial/serial.o \
			obj/kernel/arch/x64/vga.o \
			obj/kernel/arch/x64/idt.o \
			obj/kernel/arch/x64/interruptstub.o \
			obj/kernel/mem/bitmap.o \
			obj/kernel/mem/pmm.o \
			obj/utils/log.o \
			obj/klib/stdio.o \
			obj/klib/string.o \
			obj/kernel/core/kernel.o 

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
# qemu-system-x86_64.exe -cdrom $(ISO_FILENAME) -serial file:"serial.log"
	$(QEMU_SYSTEM) -monitor unix:qemu-monitor-socket,server,nowait -cpu qemu64,+x2apic  -cdrom $(ISO_FILENAME) -serial file:"serial.log" -m 1G -no-reboot -no-shutdown

buildRun: build run