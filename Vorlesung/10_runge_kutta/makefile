.PHONY: clean, mrproper
CC = g++
CFLAGS = -g -Wall

all: runge_kutta
	./runge_kutta

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

runge_kutta: runge_kutta.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f *.o core.*
	rm -f runge_kutta

