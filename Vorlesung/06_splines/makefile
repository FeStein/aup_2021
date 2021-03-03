.PHONY: clean, mrproper
CC = g++
CFLAGS = -g -Wall

all: splines
	./splines

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

splines: splines.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f *.o core.*
	rm -f splines

