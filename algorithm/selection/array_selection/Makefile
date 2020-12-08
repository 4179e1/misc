OBJ = test.o min_maximum.o randomized_select.o
CC = gcc
BASE_PATH = ../../base/
CFLAGS = -Wall -I$(BASE_PATH)

all: $(OBJ)
	$(CC) $(OBJ) -o test $(CFLAGS) -L$(BASE_PATH) -lbase
	
