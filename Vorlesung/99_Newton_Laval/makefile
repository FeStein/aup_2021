.PHONY: clean
CC = g++
CFLAGS = -g -Wall -std=c++11

all: newton
	./newton

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

newton: newton.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f *.o core.*
	rm -f newton

