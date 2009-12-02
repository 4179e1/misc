OBJ = test.o insert_sort.o selection_sort.o merge_sort.o bubble_sort.o quick_sort.o
CC = gcc
BASE_PATH = ../../base/
CFLAGS = -Wall -I$(BASE_PATH)

all: $(OBJ)
	$(CC) $(OBJ) -o test $(CFLAGS) -L$(BASE_PATH) -lbase
	
