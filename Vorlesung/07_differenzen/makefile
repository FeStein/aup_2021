.PHONY: clean, mrproper
CC = g++
CFLAGS = -g -Wall

all: balken
	./balken

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

balken: balken.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f *.o core.*
	rm -f balken

