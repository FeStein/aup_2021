.PHONY: clean, mrproper
CC = g++
CFLAGS = -g -Wall

all: main
	./main

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

main: main.o integration.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f *.o core.*
	rm -f main

