.PHONY: clean, mrproper
CC = g++
CFLAGS = -g -Wall

all: leastsquares
	./leastsquares

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

leastsquares: leastsquares.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f *.o core.*
	rm -f leastsquares

