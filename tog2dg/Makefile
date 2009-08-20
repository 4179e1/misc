GLIB = $(shell pkg-config --libs --cflags glib-2.0)
OPT = -Wall 
OBJ = malloc quark debugging

all: $(OBJ)

malloc: malloc.c
	gcc malloc.c -o malloc $(GLIB) $(OPT)
quark: quark.c
	gcc $< -o $@ $(GLIB) $(OPT)
debugging: debugging.c
	gcc $< -o $@ $(GLIB) $(OPT)

clean:
	rm $(OBJ)
