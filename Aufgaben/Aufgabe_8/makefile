.PHONY: clean
CC = g++
CFLAGS = -g -Wall -std=c++11

all: a8
	./a8

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

a8: a8.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f *.o core.*
	rm -f a8
	rm -f output*

