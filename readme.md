1. creating the object file using nasm compiler:
nasm -f elf32 kernel.asm -o kasm.o
gcc -m32 -c kernel.c -o kc.o
ld -m i386pe -T link.ld -o kernel kasm.o kc.o -build-id=none
objcopy -O elf32-i386 kernel kernel.elf

2. Test on emulator
qemu-system-i386 -kernel kernel.elf