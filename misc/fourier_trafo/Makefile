filename=main

main: 	${filename}.cpp
		g++ -c integ_algo.cpp -o integ_algo.o
		g++ -c ${filename}.cpp -o ${filename}.o
		g++ main.o integ_algo.o -o fourier.o
		./fourier.o
		python3 help.py 1

new: 	${filename}.cpp
		g++ -c integ_algo.cpp -o integ_algo.o
		g++ -c ${filename}.cpp -o ${filename}.o
		g++ main.o integ_algo.o -o fourier.o
		python3 help.py 0
		./fourier.o
		python3 help.py 1

run: 	fourier.o
		./fourier.o
		python3 help.py 1
