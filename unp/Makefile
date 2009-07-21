CC = gcc
TAR = daytimetcpcli daytimetcpsrv
OBJ = error.o wraplib.o wrapsock.o wrapunix.o
OPT = -Wall

all: $(TAR)

daytimetcpsrv: daytimetcpsrv.o $(OBJ)
	$(CC) $< $(OBJ) -o $@ $(OPT)
daytimetcpsrv.o: daytimetcpsrv.c
	$(CC) -c $< -o $@ $(OPT)

daytimetcpcli: daytimetcpcli.o $(OBJ)
	$(CC) $< $(OBJ) -o $@ $(OPT)
daytimetcpcli.o: daytimetcpcli.c
	$(CC) -c $< -o $@ $(OPT)

error.o: error.c unp.h
	$(CC) -c error.c -o error.o $(OPT)
wrapsock.o: wrapsock.c unp.h
	$(CC) -c $< -o $@ $(OPT)
wrapunix.o: wrapunix.c unp.h
	$(CC) -c $< -o $@ $(OPT)
wraplib.o: wraplib.c unp.h
	$(CC) -c $< -o $@ $(OPT)

clean:
	rm $(OBJ) $(TAR)
