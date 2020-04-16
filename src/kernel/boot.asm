section .multiboot
    header_start:
        dd 0xe85250d6
        dd 0
        dd header_end - header_start
        dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))
    mb2_tag_info_start:
        dw 1
        dw 0 ; Non-optional
        dd mb2_tag_info_end - mb2_tag_info_start
        dd 1
        dd 2
        dd 4
        dd 6
    mb2_tag_info_end:
        align 8
    mb2_tag_end_start:
        dw 0
        dw 0
        dd mb2_tag_end_end - mb2_tag_end_start
    mb2_tag_end_end:
    header_end:

section .start_section
    dd _start

; Initialize stack
section .bss
    align 16
    global STACK_BOTTOM
    global STACK_TOP

    STACK_BOTTOM:
        resb 0x4000
    STACK_TOP:

section .text
    global _start
    extern kernel_main
    _start:
        mov esp, STACK_TOP
        push ebx
        push eax
        cli
        call kernel_main
        cli
        jmp $

    global jump_userspace
    jump_userspace:
        cli
        push ebp
        mov ebp, esp
        mov edx, dword [esp + 0xC]
        mov esp, edx
        push 0xABCDEF

        mov ax, 0x23
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax

        mov eax, esp
        push 0x23
        push eax
        pushf

        ; Enable interrupts
        pop eax
        or eax, 0x200
        push eax

        push 0x1B
        push dword [ebp + 8]
        iret

        pop ebp
        ret

section .end_section
    global ASM_KERNEL_END
    ASM_KERNEL_END:
        ; Kernel size detection
