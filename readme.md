1. creating the object file using nasm compiler:
nasm -f elf32 kernel.asm -o kasm.o
gcc -m32 -c kernel.c -o kc.o
ld -m i386pe -T link.ld -o kernel kasm.o kc.o -build-id=none
objcopy -O elf32-i386 kernel kernel.elf

2. Test on emulator
qemu-system-i386 -kernel kernel.elf


![image](https://github.com/Malaysanghvi17/custom-kernel/assets/127402092/9458fa16-4061-4a23-8073-a77df2fd2e01)






This blog(https://arjunsreedharan.org/post/82710718100/kernels-101-lets-write-a-kernel) motivated me to create my own kernel.
