.PHONY: clean
CC = g++
CFLAGS = -g -Wall -std=c++11

all: main
	./main

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

main: main.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f *.o core.*
	rm -f main

