; boot.asm
[BITS 16]
[ORG 0x7C00]

jmp 0x0000:start

start:
    mov ax, 0x07C0
    add ax, 288
    mov ss, ax
    mov sp, 4096

    mov ax, 0x0000
    mov ds, ax
    mov es, ax

    call load_kernel

    cli
    hlt

load_kernel:
    mov si, kernel_message
    call print_string
    jmp $

print_string:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp print_string
.done:
    ret

kernel_message db 'Loading kernel...', 0

times 510-($-$$) db 0
dw 0xAA55
