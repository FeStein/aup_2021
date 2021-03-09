.PHONY: clean, mrproper
CC = g++
CFLAGS = -g -Wall

all: fourier
	./fourier

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

fourier: fourier.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f *.o core.*
	rm -f fourier

