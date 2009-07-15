OBJ = main.o idsl_stack.o _idsl_bintree.o

TAR: $(OBJ)
	gcc $(OBJ) -o main -Wall
main.o: main.c
	gcc main.c -c -o main.o -Wall
idsl_stack.o: idsl_stack.c idsl_stack.h
	gcc idsl_stack.c -c -o idsl_stack.o -Wall
_idsl_bintree.o: _idsl_bintree.c _idsl_bintree.h
	gcc _idsl_bintree.c -c -o _idsl_bintree.o -Wall

clean:
	rm $(OBJ) main
