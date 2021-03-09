.PHONY: clean, mrproper
CC = g++
CFLAGS = -g -Wall

all: gauss_test
	./gauss_test

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

gauss_test: gauss_test.o gauss_func.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f *.o core.*
	rm -f gauss_test

