; Multiboot header constants
MBALIGN     equ 1 << 0
MEMINFO     equ 1 << 1
FLAGS       equ MBALIGN | MEMINFO
MAGIC       equ 0x1BADB002
CHECKSUM    equ -(MAGIC + FLAGS)

; Multiboot section GRUB / QEMU sathi
section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

; Stack memory reserve karne (16 KB)
section .bss
align 16
stack_bottom:
    resb 16384 ; 16 KiB stack
stack_top:

; CPU execution entry point
section .text
global _start
extern kernel_main

_start:
    ; Stack pointer (ESP) set karne
    mov esp, stack_top

    ; CPU Flags clear karne
    push 0
    popf

    ; C++ kernel call karne
    call kernel_main

    ; Jar kernel band zala tar CPU la infinite loop madhe halt thevne
    cli
.hang:
    hlt
    jmp .hang
