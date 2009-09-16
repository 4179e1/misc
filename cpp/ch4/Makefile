CXX = g++
OPT = -Wall
TAR = 4.1

all: $(TAR)

4.1: 4.1.cpp Stack.o
	$(CXX) $< Stack.o -o $@ $(OPT)

Stack.o: Stack.cpp Stack.h
	$(CXX) $< -o $@ -c $(OPT)

clean:
	rm Stack.o $(TAR)
