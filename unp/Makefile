CC = gcc
TAR = daytimetcpcli daytimetcpsrv tcpserv01
OBJ = error.o wraplib.o wrapsock.o wrapunix.o wrapstdio.o str.o rw.o
OPT = -Wall

all: $(TAR)

tcpserv01: tcpserv01.c $(OBJ)
	$(CC) $< $(OBJ) -o $@ $(OPT)

daytimetcpsrv: daytimetcpsrv.c $(OBJ)
	$(CC) $< $(OBJ) -o $@ $(OPT)

daytimetcpcli: daytimetcpcli.c $(OBJ)
	$(CC) $< $(OBJ) -o $@ $(OPT)

error.o: error.c unp.h
	$(CC) -c error.c -o error.o $(OPT)
wrapsock.o: wrapsock.c unp.h
	$(CC) -c $< -o $@ $(OPT)
wrapunix.o: wrapunix.c unp.h
	$(CC) -c $< -o $@ $(OPT)
wraplib.o: wraplib.c unp.h
	$(CC) -c $< -o $@ $(OPT)
wrapstdio.o: wrapstdio.c unp.h
	$(CC) -c $< -o $@ $(OPT)
str.o: str.c unp.h
	$(CC) -c $< -o $@ $(OPT)
rw.o: rw.c unp.h
	$(CC) -c $< -o $@ $(OPT)

clean:
	rm $(OBJ) $(TAR)
