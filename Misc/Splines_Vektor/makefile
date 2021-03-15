.PHONY: clean
CC = g++
CFLAGS = -g -Wall -std=c++11

all: main input
	./main

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

main: main.o
	$(CC) $(CFLAGS) -o $@ $+

input: make_dat.py
	python3 make_dat.py

clean:
	rm -f *.o core.*
	rm -f main
	rm -f output
	rm -f input

