.PHONY: clean, mrproper
CC = g++
CFLAGS = -g -Wall

all: temp_explizit
	./temp_explizit

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

temp_explizit: temp_explizit.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f *.o core.*
	rm -f temp_explizit

