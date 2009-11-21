TAR = id3e
OBJ = main.o id3e.o list.o callback.o id3.o id3v1.o enc.o gva.o gv1.o genre.o wrap.o

CC = gcc
OPT = -DG_LOG_DOMAIN=\"ID3_Editor\" -Wall
DEP = id3e.h Makefile
FLAGS = $(shell pkg-config --cflags gtk+-2.0 gmodule-2.0)
LIBS = $(shell pkg-config --libs gtk+-2.0 gmodule-2.0)

$(TAR): $(OBJ) $(DEP)
	$(CC) $(OBJ) -o $@ $(LIBS) $(OPT)
main.o: main.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
id3e.o: id3e.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
list.o: list.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
callback.o: callback.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
id3.o: id3.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
id3v1.o: id3v1.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
enc.o: enc.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
gva.o: gva.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
gv1.o: gv1.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
genre.o: genre.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)
wrap.o: wrap.c $(DEP)
	$(CC) -c $< -o $@ $(FLAGS) $(OPT)

clean:
	rm $(TAR) $(OBJ)
