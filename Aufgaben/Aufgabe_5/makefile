.PHONY: clean, mrproper
CC = g++
CFLAGS = -g -Wall -std=c++11

all: a5
	./a5

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

a5: a5.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f *.o core.*
	rm -f a5

