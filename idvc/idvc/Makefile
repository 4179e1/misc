TAR = idvc
OBJ = main.o idvc.o idvc_list.o

CC = gcc
OPT = -Wall
FLAGS = `pkg-config --cflags gtk+-2.0`
LIBS = `pkg-config --libs gtk+-2.0`

$(TAR): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS) $(OPT) 
main.o: main.c
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
idvc.o: idvc.c
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
idvc_list.o: idvc_list.c
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)

clean:
	rm $(TAR) $(OBJ)
