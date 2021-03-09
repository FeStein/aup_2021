.PHONY: clean, mrproper
CC = g++
CFLAGS = -g -Wall

all: sp
	./sp

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

sp: sp.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f *.o core.*
	rm -f sp

