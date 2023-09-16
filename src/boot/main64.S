global long_mode_start
extern kernel_main

section .text
bits 64
long_mode_start:
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

  ; print 'ok'
    call kernel_main
kernel_hang:
   hlt
   jmp kernel_hang
   