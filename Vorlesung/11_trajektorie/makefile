.PHONY: clean, mrproper
CC = g++
CFLAGS = -g -Wall

all: trajektorie
	./trajektorie

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

trajektorie: trajektorie.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f *.o core.*
	rm -f trajektorie

