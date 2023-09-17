# Potatos 64
## TODO
* ✔️ cross compilation compiler
* ✔️ makefile template
* ✔️ linker script with higher half
* ✔️ gdt
* ✔️ serial port
* ✔️ higher half kernel
* ✔️ idt and handlers
* ✔️ long mode
* acpi tables
* apic
* timer (pit, hpet, local apic timer)
* keyboard support
* handling keyboard interrupt
* keyboard driver implementation
* video output (and framebuffer)
* plotting pixel
* drawing fonts
* memory management:
	* pmm
	* vmm
	* heap allocator
* physical memory manager
	* bitmap
	* returning an address
	* freeing a page
* paging
	* paging in long mode
	* loading the root table and enable paging
	* pml4, pdr, pd
	* page table/directory entry fields
* address translation
* page fault
* accessing page tables and physical memory
* virtual memory manager
	* allocating
	* freeing
* heap allocation
	* allocating
	* freeing
* scheduling and processes
	* scheluder
	* saving and restoring context
	* task
	* the idle process
	* creating new process
	* virtual memory allocator
* lock
* atomic operation support
* getting to usermode
* getting back to kernel mode
* loading tss
* tss and smp
* system calls
* vfs
	* mounting fs
	* unmounting fs
	* access a file
* tar file system
	* header
	* searching for a file
	* reading from a file
	* closing a file
* loading elfs
	* loading program header
	* loading program flags
	* running a elf
	
	