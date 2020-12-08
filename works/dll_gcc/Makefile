CC = gcc

A_OUT = test
O_FILES = main.o libtest.so

$(A_OUT): $(O_FILES)
	$(CC) main.o -o $(A_OUT) -L. -ltest
main.o: main.c
	$(CC) main.c -o main.o -c -Wall
libtest.so: libtest.c
	$(CC) libtest.c -shared -o libtest.so 

clean:
	del $(A_OUT) $(O_FILES)
