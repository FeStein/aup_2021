filename=main

main: 	${filename}.cpp
		g++ -c integ_algo.cpp -o integ_algo.out
		g++ -c ${filename}.cpp -o ${filename}.out
		g++ main.out integ_algo.out -o integ.o
		./integ.o

run: 	${filename}.out
		./integ.out

clean:
	rm *.o
	rm *.out
