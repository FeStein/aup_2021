filename=main

all: ${filename}.cpp
	g++ ${filename}.cpp -o ${filename}.o
	./${filename}.o
	python3 plot.py -f schwing.dat

run: ${filename}.o
	./${filename}.o

clean:
	rm *.o
	rm *.out
