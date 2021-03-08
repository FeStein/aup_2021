.PHONY: clean, mrproper
CC = g++
CFLAGS = -g -Wall

all: temp_implizit
	./temp_implizit

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

temp_implizit: temp_implizit.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f *.o core.*
	rm -f temp_implizit

