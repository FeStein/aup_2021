.PHONY: clean, mrproper
CC = g++
CFLAGS = -g -Wall

all: newton
	./newton

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

newton: newton.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f *.o core.*
	rm -f newton

