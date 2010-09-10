TAR = test
OBJ = main.o myipaddress.o

OPT = -Wall -O2
GTKFLAGS = $(shell pkg-config --cflags gtk+-2.0 gmodule-2.0)
LIBS = $(shell pkg-config --libs gtk+-2.0 gmodule-2.0)

CC = gcc
CFLAGS = $(GTKFLAGS) $(OPT) 

all: $(OBJ)
	$(CC) $(OBJ) -o $(TAR) $(CFLAGS) $(LIBS)

$(OBJ) : %.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY : clean	
clean:
	$(RM) $(TAR) $(OBJ)
