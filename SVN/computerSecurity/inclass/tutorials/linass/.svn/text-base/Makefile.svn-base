CLEAN   = rm
NASM    = nasm
LD      = ld
32BIT   = -m elf_i386

#g++ -z execstack -o executable_name <list of .o files>

hello: hello.o
	$(LD) $(32BIT) -o $@ $@.o

hello.o: hello.asm
	$(NASM) -f elf $@.asm

threeArgs: threeArgs.o
	$(LD) $(32BIT) -o $@ $@.o

threeArgs.o: threeArgs.asm
	$(NASM) -f elf $@.asm
