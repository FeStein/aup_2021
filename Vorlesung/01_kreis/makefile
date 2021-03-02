.PHONY: clean, mrproper
CC = g++
CFLAGS = -g -Wall

all: kreis
	./kreis

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

kreis: kreis.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f *.o core.*

mrproper: clean
	rm -f kreis

