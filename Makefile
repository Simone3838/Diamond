# Makefile
CXX = i686-elf-g++
LD = i686-elf-ld
AS = nasm

CXXFLAGS = -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T linker.ld -nostdlib

all: os.iso

os.iso: boot.bin kernel.bin
    mkdir -p iso/boot/grub
    cp boot.bin iso/boot/
    cp kernel.bin iso/boot/
    echo 'set timeout=0' > iso/boot/grub/grub.cfg
    echo 'set default=0' >> iso/boot/grub/grub.cfg
    echo 'menuentry "Boot OS" {' >> iso/boot/grub/grub.cfg
    echo '  multiboot /boot/kernel.bin' >> iso/boot/grub/grub.cfg
    echo '}' >> iso/boot/grub/grub.cfg
    grub-mkrescue -o os.iso iso

boot.bin: boot.asm
    $(AS) -f bin -o boot.bin boot.asm

kernel.bin: kernel_entry.o kernel.o
    $(LD) $(LDFLAGS) -o kernel.bin kernel_entry.o kernel.o

kernel_entry.o: kernel_entry.asm
    $(AS) -f elf32 -o kernel_entry.o kernel_entry.asm

kernel.o: kernel.cpp
    $(CXX) $(CXXFLAGS) -c kernel.cpp -o kernel.o

clean:
    rm -rf *.o *.bin iso os.iso
