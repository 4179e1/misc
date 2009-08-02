OBJ = main.o idsl_stack.o _idsl_bintree.o _idsl_bstree.o idsl_bstree.o _idsl_node.o _idsl_list.o idsl_list.o
CC = gcc
OPT = -Wall

TAR: $(OBJ)
	$(CC) $(OBJ) -o main $(OPT)
main.o: main.c
	$(CC) main.c -c -o main.o $(OPT)
idsl_stack.o: idsl_stack.c idsl_stack.h
	$(CC) idsl_stack.c -c -o idsl_stack.o $(OPT)
_idsl_bintree.o: _idsl_bintree.c _idsl_bintree.h
	$(CC) _idsl_bintree.c -c -o _idsl_bintree.o $(OPT)
_idsl_bstree.o: _idsl_bstree.c _idsl_bstree.h
	$(CC) _idsl_bstree.c -c -o _idsl_bstree.o $(OPT)
idsl_bstree.o: idsl_bstree.c idsl_bstree.h
	$(CC) -c $< -o $@ $(OPT)
_idsl_node.o: _idsl_node.c _idsl_node.h
	$(CC) -c $< -o $@ $(OPT)
_idsl_list.o: _idsl_list.c _idsl_list.h
	$(CC) -c $< -o $@ $(OPT)
idsl_list.o: idsl_list.c idsl_list.h
	$(CC) -c $< -o $@ $(OPT)

clean:
	rm $(OBJ) main
clean2:
	del $(OBJ) main.exe
