OBJ = hello check_sum sum reverse
ASM=nasm

.PHONY: all clean
all: $(OBJ)

$(OBJ) : % : %.asm
	$(ASM) -f elf64 -o $@.o $<
	ld -o $@ $@.o
	rm $@.o

clean:
	$(RM) $(OBJ) *.o
