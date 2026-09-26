AS = nasm
CC = g++
LD = ld

ASFLAGS = -f elf32
CXXFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
LDFLAGS = -m elf_i386 -T linker.ld

OBJS = boot.o kernel.o

all: myos.bin

boot.o: boot.asm
	$(AS) $(ASFLAGS) boot.asm -o boot.o

kernel.o: kernel.cpp
	$(CC) $(CXXFLAGS) -c kernel.cpp -o kernel.o

myos.bin: $(OBJS)
	$(LD) $(LDFLAGS) -o myos.bin $(OBJS)

clean:
	rm -f $(OBJS) myos.bin
