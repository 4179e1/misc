TAR = idve
OBJ = main.o idve.o callback.o

CC = gcc
OPT = -DG_LOG_DOMAIN=\"IDV_Editor\" -Wall -g
DEP = idve.h Makefile
FLAGS = $(shell pkg-config --cflags gtk+-2.0 gmodule-2.0 gthread-2.0)
LIBS = $(shell pkg-config --libs gtk+-2.0 gmodule-2.0 gthread-2.0)

$(TAR): $(OBJ) $(DEP)
	$(CC) $(OBJ) -o $@ $(LIBS) $(OPT)
main.o: main.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
idve.o: idve.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
callback.o: callback.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)

clean:
	rm $(TAR) $(OBJ)
