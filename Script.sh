nasm -f elf32 enmascarar.asm -o Enmascarar.o;
gcc -m32 -o ejecutable Enmascarar.o enmascarar.c;
