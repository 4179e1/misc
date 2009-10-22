TAR = idvc
OBJ = main.o idvc.o idvc_list.o idvc_menu.o idvc_toolbar.o

CC = gcc
OPT = -Wall
FLAGS = $(shell pkg-config --cflags gtk+-2.0)
LIBS = $(shell pkg-config --libs gtk+-2.0)

$(TAR): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS) $(OPT) 
main.o: main.c
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
idvc.o: idvc.c
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
idvc_list.o: idvc_list.c
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
idvc_menu.o: idvc_menu.c
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
idvc_toolbar.o: idvc_toolbar.c
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)

clean:
	rm $(TAR) $(OBJ)
