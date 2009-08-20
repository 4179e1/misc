all: pre asm obj bin
	
pre: test.c
	gcc -E test.c -o test.i
asm: test.c
	gcc -S test.c -o test.s
obj: test.c
	gcc -c test.c -o test.o
bin: test.c
	gcc test.c -o test

dep: test.c
	gcc -M test.c

clean: 
	rm test.i test.s test.o test
