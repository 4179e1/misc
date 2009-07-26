OBJ = main.o idsl_stack.o _idsl_bintree.o _idsl_bstree.o idsl_bstree.o
CC = gcc

TAR: $(OBJ)
	$(CC) $(OBJ) -o main -Wall
main.o: main.c
	$(CC) main.c -c -o main.o -Wall
idsl_stack.o: idsl_stack.c idsl_stack.h
	$(CC) idsl_stack.c -c -o idsl_stack.o -Wall
_idsl_bintree.o: _idsl_bintree.c _idsl_bintree.h
	$(CC) _idsl_bintree.c -c -o _idsl_bintree.o -Wall
_idsl_bstree.o: _idsl_bstree.c _idsl_bstree.h
	$(CC) _idsl_bstree.c -c -o _idsl_bstree.o -Wall
idsl_bstree.o: idsl_bstree.c idsl_bstree.h
	$(CC) -c $< -o $@ -Wall

clean:
	rm $(OBJ) main
clean2:
	del $(OBJ) main.exe
