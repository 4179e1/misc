OBJ = 1 2 3
ASM=nasm

.PHONY: all clean
all: $(OBJ)

$(OBJ) : % : %.asm
	$(ASM) -f elf64 -o $@.o $<
	ld -o $@ $@.o
	rm $@.o

clean:
	$(RM) $(OBJ) *.o
