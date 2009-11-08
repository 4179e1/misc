TAR = id3e
OBJ = main.o id3e.o callback.o id3v1.o

CC = gcc
OPT = -DG_LOG_DOMAIN=\"ID3_Editor\" -Wall -g
DEP = id3e.h Makefile
FLAGS = $(shell pkg-config --cflags gtk+-2.0 gmodule-2.0)
LIBS = $(shell pkg-config --libs gtk+-2.0 gmodule-2.0)

$(TAR): $(OBJ) $(DEP)
	$(CC) $(OBJ) -o $@ $(LIBS) $(OPT)
main.o: main.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
id3e.o: id3e.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
callback.o: callback.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
id3v1.o: id3v1.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)

clean:
	rm $(TAR) $(OBJ)
