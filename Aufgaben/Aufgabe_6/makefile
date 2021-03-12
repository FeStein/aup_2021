.PHONY: clean
CC = g++
CFLAGS = -g -Wall -std=c++11

all: a6
	./a6

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

a6: a6.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f *.o core.*
	rm -f a6

