.PHONY: clean
CC = g++
CFLAGS = -g -Wall -std=c++11

all: a7
	./a7

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

a7: a7.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f *.o core.*
	rm -f a7

