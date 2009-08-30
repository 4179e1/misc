CC = gcc
TAR = daytimetcpcli daytimetcpsrv tcpserv01 tcpcli tcpcli04 tcpservselect01 tcpservpoll01 checkopts
OBJ = error.o wraplib.o wrapsock.o wrapunix.o wrapstdio.o str.o rw.o signal.o
OPT = -Wall

all: $(TAR)
checkopts: checkopts.c $(OBJ)
	$(CC) $< $(OBJ) -o $@ $(OPT)
tcpservpoll01: tcpservpoll01.c $(OBJ)
	$(CC) $< $(OBJ) -o $@ $(OPT)
tcpservselect01: tcpservselect01.c $(OBJ)
	$(CC) $< $(OBJ) -o $@ $(OPT)
tcpcli04: tcpcli04.c $(OBJ)
	$(CC) $< $(OBJ) -o $@ $(OPT)
tcpcli: tcpcli.c $(OBJ)
	$(CC) $< $(OBJ) -o $@ $(OPT)
tcpserv01: tcpserv01.c $(OBJ)
	$(CC) $< $(OBJ) -o $@ $(OPT)
daytimetcpsrv: daytimetcpsrv.c $(OBJ)
	$(CC) $< $(OBJ) -o $@ $(OPT)
daytimetcpcli: daytimetcpcli.c $(OBJ)
	$(CC) $< $(OBJ) -o $@ $(OPT)

error.o: error.c 
	$(CC) -c error.c -o error.o $(OPT)
wrapsock.o: wrapsock.c 
	$(CC) -c $< -o $@ $(OPT)
wrapunix.o: wrapunix.c 
	$(CC) -c $< -o $@ $(OPT)
wraplib.o: wraplib.c 
	$(CC) -c $< -o $@ $(OPT)
wrapstdio.o: wrapstdio.c 
	$(CC) -c $< -o $@ $(OPT)
str.o: str.c 
	$(CC) -c $< -o $@ $(OPT)
rw.o: rw.c 
	$(CC) -c $< -o $@ $(OPT)
signal.o: signal.c 
	$(CC) -c $< -o $@ $(OPT)

clean:
	rm $(OBJ) $(TAR)
