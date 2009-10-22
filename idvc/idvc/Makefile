TAR = idvc
OBJ = main.o idvc.o idvc_list.o idvc_menu.o idvc_toolbar.o

CC = gcc
OPT = -DG_LOG_DOMAIN=\"IDV_Converter\" -Wall -g
DEP = idvc.h Makefile
FLAGS = $(shell pkg-config --cflags gtk+-2.0)
LIBS = $(shell pkg-config --libs gtk+-2.0)

$(TAR): $(OBJ) $(DEP)
	$(CC) $(OBJ) -o $@ $(LIBS) $(OPT)
main.o: main.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
idvc.o: idvc.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
idvc_list.o: idvc_list.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
idvc_menu.o: idvc_menu.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
idvc_toolbar.o: idvc_toolbar.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)

clean:
	rm $(TAR) $(OBJ)
