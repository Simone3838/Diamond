; kernel_entry.asm
[BITS 32]
[GLOBAL kernel_entry]

kernel_entry:
    cli
    cld
    call kernel_main
    hlt
