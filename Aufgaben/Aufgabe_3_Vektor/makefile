.PHONY: clean, mrproper
CC = g++
CFLAGS = -g -Wall

all: fourier input plot.py
	./fourier
	python3 plot.py

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

fourier: fourier.o
	$(CC) $(CFLAGS) -o $@ $+

input: func.py
	python3 func.py

clean:
	rm -f *.o core.*
	rm -f fourier

